# LLM Track Reference

Use this only for the minimal-LLM short-term project. Adapt pace to the learner's evidence, not to the calendar.

Use `topics/llm/learning/roadmap.md` as the learner's canonical progress plan. Its milestones map to public teaching material rather than an official spec:

- M0-M1 follow Andrej Karpathy's [makemore](https://github.com/karpathy/makemore) (bigram section).
- M2-M3 follow Andrej Karpathy's [Let's build GPT](https://github.com/karpathy/ng-video-lecture), cross-checked against [nanoGPT](https://github.com/karpathy/nanoGPT)'s `model.py` for the finished shape.
- M4 follows nanoGPT's train/val split and sampling (`generate`) logic.
- [Attention Is All You Need](https://arxiv.org/abs/1706.03762) is a conceptual reference for self-attention (§3.2) only; do not assign it as reading in full.

## Recommended progression

1. Tensors, autograd, and one manual training loop (M0) before any language modeling.
2. A character-level bigram model as the smallest complete pipeline: text -> vocab -> encode -> embedding lookup -> cross-entropy -> backward -> sample (M1). This is the session's primary deliverable evidence for "minimal but complete."
3. One self-attention head added to the same model, with a causal mask (M2).
4. Multi-head attention, feedforward block, residual connections, LayerNorm, stacked into blocks (M3).
5. Train/val split and temperature/top-k sampling as the closing lesson (M4).

## Coaching prompts

- "What does this token see right now — only the previous character, or the whole prefix?"
- "If you removed the causal mask, what would change during generation?"
- "Which line turns a raw text file into something a neural network can consume?"
- "What exact command and printed loss value supports the claim that this milestone works?"

## Avoid early

Avoid BPE/subword tokenizers, `nn.MultiheadAttention`/`nn.Transformer` shortcuts, multi-GPU or distributed training, and instruction tuning/RLHF until the learner has hand-built and explained the bigram and single-head attention stages. Introduce a high-level library equivalent only as a post-hoc comparison, never as a replacement for the hand-written version this project is built around.

## Dataset and scale guidance

Keep the training corpus small (a few hundred KB at most) so CPU/`mps` training finishes in seconds to a few minutes per experiment. Prefer iteration speed and a visible loss curve over model quality. If the learner wants closer-to-real results after M4, point to swapping in the full `tiny-shakespeare` corpus and nanoGPT's default hyperparameters as a follow-up outside this short-term project's scope.
