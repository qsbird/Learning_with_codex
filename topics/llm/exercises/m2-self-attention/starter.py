"""M2: single-head self-attention with a causal mask.

Read exercises/m2-self-attention/README.md before filling in the TODOs.
This extends M1's bigram model: instead of only looking at the single
previous character, the model can now attend to every earlier character
inside a fixed-size context window (block_size).
"""

import math
from pathlib import Path

import torch
import torch.nn as nn
from torch.nn import functional as F

CORPUS_PATH = Path(__file__).parent.parent / "m1-bigram" / "data" / "corpus.txt"
BATCH_SIZE = 32
BLOCK_SIZE = 16   # context window: how many previous characters the model can attend to
N_EMBD = 32       # size of each token's embedding vector
HEAD_SIZE = 16    # size of the Q/K/V projection for this single attention head
TRAIN_STEPS = 3000
LEARNING_RATE = 1e-2


def pick_device() -> torch.device:
    if torch.backends.mps.is_available():
        return torch.device("mps")
    return torch.device("cpu")


class SelfAttentionLanguageModel(nn.Module):
    def __init__(self, vocab_size: int, n_embd: int, block_size: int, head_size: int):
        super().__init__()
        self.head_size = head_size
        self.token_embedding = nn.Embedding(vocab_size, n_embd)

        # TODO 1: create a second embedding table for POSITIONS (not characters).
        # It should have `block_size` rows and `n_embd` columns: one learnable
        # vector per position 0..block_size-1, so the model can tell "this is
        # the 3rd character in the window" apart from just knowing which
        # character it is.
        self.position_embedding = nn.Embedding(block_size, n_embd) # replace: None
        # TODO 2: create the three linear projections for self-attention.
        # Each maps an n_embd-dim vector to a head_size-dim vector.
        # bias=False is conventional here (not required, just standard practice).
        self.key = nn.Linear(n_embd, head_size, bias=False)
        self.query = nn.Linear(n_embd, head_size, bias=False) # replace: None
        self.value = nn.Linear(n_embd, head_size, bias=False) # replace: None

        # A causal mask: tril[i, j] == 1 means position i is allowed to look at
        # position j. register_buffer stores this like a parameter (it moves
        # with .to(device)) but it is NOT trained -- it's a fixed 0/1 pattern.
        self.register_buffer("tril", torch.tril(torch.ones(block_size, block_size)))

        self.lm_head = nn.Linear(head_size, vocab_size)

    def forward(self, idx: torch.Tensor) -> torch.Tensor:
        B, T = idx.shape
        tok_emb = self.token_embedding(idx)  # (B, T, n_embd)
        pos_emb = self.position_embedding(torch.arange(T, device=idx.device))  # (T, n_embd)

        # TODO 1 (continued): combine the two embeddings into one (B, T, n_embd)
        # tensor. Broadcasting handles the shape mismatch, same idea as M0.
        x = tok_emb + pos_emb

        # TODO 2 (continued): project x into key/query/value vectors.
        k = self.key(x)     # (B, T, head_size)
        q = self.query(x)   # (B, T, head_size)
        v = self.value(x)   # (B, T, head_size)

        # TODO 3: compute raw attention scores (affinities) between every pair
        # of positions, scaled by head_size**-0.5, then apply the causal mask
        # so a position cannot see the future, then softmax to get weights
        # that sum to 1 across the last dimension.
        wei = q @ k.transpose(-2, -1) * self.head_size**-0.5   # (B, T, T)
        wei = wei.masked_fill(self.tril[:T, :T] == 0, float("-inf"))
        wei = F.softmax(wei, dim=-1)

        # TODO 4: use the attention weights to mix the value vectors, then
        # project the result to vocab-sized logits with self.lm_head.
        out = wei @ v              # (B, T, head_size)
        logits = self.lm_head(out)  # (B, T, vocab_size)
        return logits


def get_batch(data: torch.Tensor, block_size: int, batch_size: int, device: torch.device):
    """Sample `batch_size` random windows of length `block_size`, and their
    one-step-shifted targets (already provided -- pure transfer of the M1 idea,
    just for a whole window instead of a single character)."""
    ix = torch.randint(0, len(data) - block_size - 1, (batch_size,))
    x = torch.stack([data[i:i + block_size] for i in ix]).to(device)
    y = torch.stack([data[i + 1:i + 1 + block_size] for i in ix]).to(device)
    return x, y


@torch.no_grad()
def generate(model: SelfAttentionLanguageModel, itos: dict, start_id: int, length: int,
             block_size: int, device: torch.device) -> str:
    """Autoregressively sample `length` characters. Unlike M1, we must keep the
    whole growing sequence (not just the last character), then crop it to the
    last `block_size` characters before each forward pass -- that crop is what
    keeps the model inside the context window it was trained with."""
    idx = torch.tensor([[start_id]], device=device)
    out_ids = [start_id]
    for _ in range(length):
        idx_cond = idx[:, -block_size:]
        logits = model(idx_cond)[:, -1, :]
        probs = F.softmax(logits, dim=-1)
        next_id = torch.multinomial(probs, num_samples=1)
        idx = torch.cat([idx, next_id], dim=1)
        out_ids.append(int(next_id))
    return "".join(itos[i] for i in out_ids)


def main() -> None:
    device = pick_device()
    print(f"using device: {device}")

    text = CORPUS_PATH.read_text(encoding="utf-8")
    chars = sorted(set(text))
    stoi = {ch: i for i, ch in enumerate(chars)}
    itos = {i: ch for ch, i in stoi.items()}
    vocab_size = len(chars)
    print(f"vocab size: {vocab_size}")
    print(f"reference loss for a uniformly random model: ln({vocab_size}) = {math.log(vocab_size):.4f}")

    data = torch.tensor([stoi[c] for c in text], dtype=torch.long)

    model = SelfAttentionLanguageModel(vocab_size, N_EMBD, BLOCK_SIZE, HEAD_SIZE).to(device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=LEARNING_RATE)

    for step in range(TRAIN_STEPS):
        xb, yb = get_batch(data, BLOCK_SIZE, BATCH_SIZE, device)
        logits = model(xb)
        loss = F.cross_entropy(logits.view(-1, vocab_size), yb.view(-1))

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if step % 300 == 0:
            print(f"step {step:4d} | loss {loss.item():.4f}")

    print(f"final loss: {loss.item():.4f}")

    start_id = stoi[text[0]]
    sample = generate(model, itos, start_id, length=200, block_size=BLOCK_SIZE, device=device)
    print("\n--- generated sample ---")
    print(sample)


if __name__ == "__main__":
    main()
