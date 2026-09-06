"""M0: fit y = 2x + 1 with a hand-written linear model and manual autograd.

Read exercises/m0-tensor-warmup/README.md before filling in the TODOs.
Do not use nn.Linear here; the point of this warmup is to see every piece
of the forward/backward/optimizer loop explicitly.
"""

import torch


def pick_device() -> torch.device:
    """Prefer Apple Silicon's mps backend, fall back to cpu."""
    if torch.backends.mps.is_available():
        return torch.device("mps")
    return torch.device("cpu")


def make_data(device: torch.device, n: int = 64):
    x = torch.linspace(-5, 5, n, device=device).unsqueeze(1)
    noise = 0.1 * torch.randn(n, 1, device=device)
    y = 2 * x + 1 + noise
    return x, y


def main() -> None:
    device = pick_device()
    print(f"using device: {device}")

    x, y = make_data(device)

    # TODO 1: create w and b as scalar tensors with requires_grad=True,
    # on the same `device` as x/y. Initialize them to any small values,
    # e.g. torch.zeros(1, ...) or torch.randn(1, ...).
    w = torch.zeros(1, requires_grad=True, device=device)
    b = torch.randn(1, requires_grad=True, device=device)

    optimizer = torch.optim.SGD([w, b], lr=0.01)

    for step in range(200):
        # TODO 2: forward pass -- compute `pred` from w, x, b.
        pred = w * x + b

        # TODO 3: mean squared error between pred and y.
        loss = ((pred - y) ** 2).mean()

        loss.backward()
        optimizer.step()
        optimizer.zero_grad()

        if step % 20 == 0:
            print(f"step {step:3d} | loss {loss.item():.4f}")

    print(f"learned w={w.item():.3f}, b={b.item():.3f} (target: w=2.0, b=1.0)")


if __name__ == "__main__":
    main()
