# Teaching PyTorch/attention syntax before an exercise

Use this reference when a lesson introduces a PyTorch or math primitive the learner has not used before. Present the relevant section before asking the learner to change a file.

## Tensors, shapes, and `requires_grad` (M0)

Show the smallest valid form in context before assigning the fitting exercise:

```python
import torch

w = torch.randn(1, requires_grad=True)
b = torch.zeros(1, requires_grad=True)

pred = w * x + b        # forward: one tensor expression
loss = ((pred - y) ** 2).mean()
loss.backward()         # fills w.grad, b.grad
```

Explain in this order: a tensor is an n-dimensional array with a dtype and device; `requires_grad=True` tells autograd to record operations on this tensor; `loss.backward()` walks the recorded graph backward and accumulates gradients into `.grad`; nothing is updated yet — that is the optimizer's job. Ask the learner to predict what `w.grad` looks like before the first `backward()` call (it is `None`).

## Optimizer step and `zero_grad` (M0)

```python
opt = torch.optim.SGD([w, b], lr=0.01)
opt.step()       # applies grad to parameters
opt.zero_grad()  # clears grad for the next iteration
```

State the boundary explicitly: `backward()` only accumulates; forgetting `zero_grad()` adds new gradients on top of old ones across iterations. Ask what would happen to training if `zero_grad()` were removed, before assigning the loop.

## Character vocabulary and encoding (M1)

```python
chars = sorted(set(text))
stoi = {ch: i for i, ch in enumerate(chars)}
itos = {i: ch for ch, i in stoi.items()}
encode = lambda s: [stoi[c] for c in s]
```

Explain that a neural network only consumes numbers, so `stoi`/`itos` are the smallest possible tokenizer: one integer id per character. Ask the learner what `len(chars)` represents (vocabulary size) before it is used as an embedding table dimension.

## `nn.Embedding` as a bigram lookup table (M1)

```python
table = nn.Embedding(vocab_size, vocab_size)
logits = table(idx)   # idx: (batch, time) -> logits: (batch, time, vocab_size)
```

Explain that `nn.Embedding(vocab_size, vocab_size)` is a lookup table with one row per possible current character, and each row's values are the (unnormalized) scores for what the next character might be — the bigram model's entire parameter set is this table. Ask what changes if the second argument were smaller than `vocab_size` (rows would be an embedding, not directly usable as next-character logits without a further projection).

## Cross-entropy loss (M1)

```python
loss = F.cross_entropy(logits.view(-1, vocab_size), targets.view(-1))
```

Explain that `cross_entropy` combines a softmax over the last dimension with negative-log-likelihood of the correct next-character index; a uniformly random model's expected loss is `ln(vocab_size)`, which gives the learner a sanity-check number to compare their initial loss against.

## Causal self-attention (M2)

Introduce the shapes before the formula:

```python
q = query(x)   # (B, T, head_size)
k = key(x)     # (B, T, head_size)
v = value(x)   # (B, T, head_size)
wei = q @ k.transpose(-2, -1) * head_size**-0.5   # (B, T, T)
wei = wei.masked_fill(causal_mask == 0, float('-inf'))
wei = F.softmax(wei, dim=-1)
out = wei @ v
```

Explain in this order: `q @ k.transpose(-2, -1)` produces one raw affinity score per (query position, key position) pair; scaling by `head_size**-0.5` keeps those scores from growing too large as `head_size` grows; `masked_fill` with `-inf` before softmax forces attention to future positions to become exactly zero after softmax, which is what makes the model causal (it cannot look ahead); the final `wei @ v` mixes value vectors according to those weights. Ask the learner to predict, for position 0, how many other positions it can attend to (only itself), before they wire the mask in.

## Residual connections and LayerNorm (M3)

```python
x = x + self.attn(self.ln1(x))
x = x + self.ffn(self.ln2(x))
```

Explain that `x + f(x)` (a residual connection) lets gradients flow directly through the `+` regardless of what `f` does, which is why stacking many blocks stays trainable; LayerNorm before each sub-layer (`ln1`, `ln2`) rescales activations so that deeper blocks see inputs in a similar range. Ask what would be lost by removing the `x +` term (the block would no longer have a direct gradient shortcut, and stacking many of them would become much harder to train) before assigning the block assembly.
