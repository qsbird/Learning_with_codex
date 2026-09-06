"""M1: a minimal character-level bigram language model.

Read exercises/m1-bigram/README.md before filling in the TODOs.
Pipeline: text -> char vocab -> integer encoding -> embedding lookup
(logits) -> cross-entropy loss -> backward -> sample to generate text.
"""

import math
from pathlib import Path

import torch
import torch.nn as nn
from torch.nn import functional as F

CORPUS_PATH = Path(__file__).parent / "data" / "corpus.txt"
BATCH_SIZE = 32
BLOCK_SIZE = 1  # a bigram only ever looks at exactly one previous character
TRAIN_STEPS = 3000
LEARNING_RATE = 1e-2


def pick_device() -> torch.device:
    if torch.backends.mps.is_available():
        return torch.device("mps")
    return torch.device("cpu")


class BigramLanguageModel(nn.Module):
    def __init__(self, vocab_size: int):
        super().__init__()
        # TODO 3: one embedding table where row i holds the logits for
        # "what comes after character i". Shape: (vocab_size, vocab_size).
        self.token_table = nn.Embedding(vocab_size, vocab_size)

    def forward(self, idx: torch.Tensor) -> torch.Tensor:
        """idx: (batch, time) integer ids -> logits: (batch, time, vocab_size)."""
        # TODO 3 (continued): look up idx in self.token_table.
        logits = self.token_table(idx)
        return logits


def get_batch(data: torch.Tensor, batch_size: int, device: torch.device):
    """Sample `batch_size` random (current_char, next_char) pairs."""
    ix = torch.randint(0, len(data) - 1, (batch_size,))
    x = data[ix].to(device)
    y = data[ix + 1].to(device)
    return x, y


@torch.no_grad()
def generate(model: BigramLanguageModel, itos: dict, start_id: int, length: int, device: torch.device) -> str:
    """Autoregressively sample `length` characters starting from start_id."""
    idx = torch.tensor([[start_id]], device=device)
    out_ids = [start_id]
    for _ in range(length):
        # TODO 6a: get logits for the current last character (idx[:, -1]).
        logits = model(idx[:, -1:])[:, -1, :]

        # TODO 6b: turn logits into probabilities and sample one next id.
        next_id = torch.multinomial(F.softmax(logits, dim=-1), num_samples=1)

        out_ids.append(int(next_id))
        idx = torch.tensor([[next_id]], device=device)
    return "".join(itos[i] for i in out_ids)


def main() -> None:
    device = pick_device()
    print(f"using device: {device}")

    text = CORPUS_PATH.read_text(encoding="utf-8")

    # TODO 1: build the character vocabulary and stoi/itos maps.
    chars = sorted(list(set(text)))
    stoi = {ch: i for i, ch in enumerate(chars)}
    itos = {i: ch for ch, i in stoi.items()}
    vocab_size = len(chars)
    print(f"vocab size: {vocab_size}")
    print(f"reference loss for a uniformly random model: ln({vocab_size}) = {math.log(vocab_size):.4f}")

    # TODO 2: encode the whole corpus into one 1D integer tensor.
    data = torch.tensor([stoi[c] for c in text], dtype=torch.long)

    model = BigramLanguageModel(vocab_size).to(device)
    optimizer = torch.optim.AdamW(model.parameters(), lr=LEARNING_RATE)

    for step in range(TRAIN_STEPS):
        xb, yb = get_batch(data, BATCH_SIZE, device)
        logits = model(xb.unsqueeze(1))  # (batch, 1, vocab_size)

        # TODO 4: cross-entropy between logits and yb.
        # Hint: logits.view(-1, vocab_size), yb.view(-1)
        loss = F.cross_entropy(logits.view(-1, vocab_size), yb.view(-1))

        # TODO 5: backward + optimizer step + zero_grad, in the right order.
        optimizer.zero_grad()
        loss.backward()
        optimizer.step()
        if step % 300 == 0:
            print(f"step {step:4d} | loss {loss.item():.4f}")

    print(f"final loss: {loss.item():.4f}")

    start_id = stoi[text[0]]
    sample = generate(model, itos, start_id, length=200, device=device)
    print("\n--- generated sample ---")
    print(sample)


if __name__ == "__main__":
    main()
