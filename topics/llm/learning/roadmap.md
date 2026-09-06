# 最小 LLM 短期项目路线

## 目标与使用方式

目标：不追求训练出可用的大模型，而是亲手体验一次完整、最小化的 LLM 工作流——**数据 → 分词（tokenizer） → 模型前向 → loss → 反向传播 → 采样生成**——并能对每一步说清楚“为什么需要它”。

本路线以 Andrej Karpathy 的公开教学材料为主线：

- [makemore](https://github.com/karpathy/makemore) 与其配套讲解视频《The spelled-out intro to language modeling》——bigram/MLP 字符级语言模型。
- [Let's build GPT: from scratch, in code, spelled out](https://github.com/karpathy/ng-video-lecture)（即 nanoGPT 的教学版本）——自注意力、多头注意力、Transformer block。
- [nanoGPT](https://github.com/karpathy/nanoGPT) 作为完成后对照的“完整版”参考实现。
- [Attention Is All You Need](https://arxiv.org/abs/1706.03762)（Vaswani et al., 2017）作为自注意力/Transformer 的概念出处，只读相关章节，不要求通读全文。
- [PyTorch 官方教程 Learn the Basics](https://pytorch.org/tutorials/beginner/basics/intro.html)——张量、autograd、`nn.Module`、优化器的权威语法参考。

开始前填写 [profile.md](profile.md)。每次学习后追加 [log.md](log.md)，并以可运行脚本、打印出的 loss 曲线、生成样例或口头解释作为完成证据。“看完视频”或“代码能跑”都不算完成——终点是能不看资料，说清楚该阶段引入的新概念。

## 每课学习方式

沿用仓库通用的学习方式：讲解新概念与最小示例 → 问答澄清 → 学习者独立完成一小段代码 → 用运行结果与口头解释收口。测试用于定位下一步该补什么，不用来打分。

## 里程碑总览

| 阶段 | 对应材料 | 建议时长 | 产出 | 完成门槛 |
|---|---|---:|---|---|
| M0：环境与张量热身 | PyTorch Learn the Basics | 0.5-1 小时 | 能跑通的最小 autograd 训练 | 能解释 forward/backward/optimizer.step 三者分工 |
| M1：最小闭环——字符级 bigram 模型 | makemore（bigram 部分） | 1.5-2.5 小时 | 能训练+生成的最小语言模型 | 能独立描述“数据→tokenizer→模型→loss→生成”全链路 |
| M2：单头自注意力 | Let's build GPT（self-attention 部分）；Attention Is All You Need §3.2 | 1.5-2.5 小时 | 在 M1 基础上加入一个注意力头 | 能解释注意力相比 bigram 多看到了什么、为何需要因果 mask |
| M3：多头注意力 + Transformer block（迷你 GPT） | Let's build GPT（完整部分）；nanoGPT 源码对照 | 2-3 小时 | 可训练的迷你 GPT（多层 block） | 能说清 attention/FFN/残差/LayerNorm 各自的职责 |
| M4：采样、验证集与收尾复盘 | nanoGPT 的 train/val 与采样逻辑 | 1-1.5 小时 | 带 train/val 曲线与可调温度采样的完整脚本 | 能解释 train/val 分离的目的与温度对生成的影响 |

时长按“今天 2-4 小时”这一档估算：M0+M1 是今天现实可完成的目标；M2-M4 按短期项目节奏分 1-2 次后续会话完成。

---

## M0 — 环境与张量/autograd 热身

对应材料：[PyTorch Learn the Basics](https://pytorch.org/tutorials/beginner/basics/intro.html) 中 Tensors、Autograd、Optimization 三节。

学习内容：`torch.tensor`、基本张量运算与形状（shape）、`requires_grad`、`loss.backward()`、`torch.optim`、设备选择（`mps` / `cpu`）。

练习：在 `exercises/m0-tensor-warmup/` 中，用手写的 `y = w*x + b` 和 SGD 优化器拟合一批 `y = 2x + 1` 的数据点，不使用 `nn.Linear`。

验证：

```sh
python3 -m venv .venv && source .venv/bin/activate  # 或已有环境
pip install torch
python3 topics/llm/exercises/m0-tensor-warmup/starter.py
```

打印出的 loss 应随迭代明显下降；脚本能自动选择 `mps`（若可用）或回退 `cpu`。

退出标准：能解释一次训练迭代里，前向计算、`loss.backward()`、`optimizer.step()`、`optimizer.zero_grad()` 各自做了什么、顺序为什么固定。

## M1 — 最小闭环：字符级 bigram 语言模型（今天的主目标）

对应材料：[makemore](https://github.com/karpathy/makemore) 的 bigram 部分（对应视频前 30-40 分钟）。

学习内容：字符级词表构建（`stoi`/`itos`）、`nn.Embedding` 作为 bigram 查表、`F.cross_entropy`、训练循环、`torch.multinomial` 采样生成。

练习：在 `exercises/m1-bigram/` 中，用 `data/corpus.txt`（已提供的小型文本）训练一个字符级 bigram 模型：给定当前字符预测下一个字符，训练若干步后生成一段文本。

验证：

```sh
python3 topics/llm/exercises/m1-bigram/starter.py
```

- loss 应从初始（约 `ln(词表大小)`）明显下降；
- 脚本运行结束打印一段生成文本（质量可以很差，但不能报错）；
- 能不看代码复述一遍完整链路：读文本 → 建词表 → 编码成整数张量 → embedding 查表得到 logits → cross-entropy → backward → 用模型采样生成。

退出标准：这一条链路——从原始文本到生成文本——由学习者独立跑通并解释清楚。这就是本项目“最小但完整流程”的核心证据。

## M2 — 单头自注意力

对应材料：[Let's build GPT](https://github.com/karpathy/ng-video-lecture) 中 self-attention 一节；[Attention Is All You Need](https://arxiv.org/abs/1706.03762) §3.2（只读 Scaled Dot-Product Attention 部分）。

学习内容：位置编码（position embedding）、Query/Key/Value 线性投影、缩放点积、因果 mask（causal mask）、softmax 得到注意力权重。

练习：在 M1 的模型上增加一个自注意力头，替换/增强原来的 bigram 查表，让模型能看到更长的上下文。

验证：同语料下，训练同样步数，loss 应低于 M1 的 bigram 基线；能对一个 4-5 个字符的小例子手算一次注意力权重。

退出标准：能解释“为什么 bigram 只看得到前一个字符，而自注意力能看到更早的上下文”，以及因果 mask 为什么必须存在。

## M3 — 多头注意力 + Transformer block（迷你 GPT）

对应材料：[Let's build GPT](https://github.com/karpathy/ng-video-lecture) 剩余部分；完成后对照 [nanoGPT](https://github.com/karpathy/nanoGPT) 的 `model.py`。

学习内容：多头注意力（多个注意力头并行再拼接）、前馈网络（FFN）、残差连接、LayerNorm、把 attention+FFN 封装成一个 block 并堆叠多层。

练习：组装一个几层、维度较小的迷你 GPT（对照 nanoGPT 但参数量小得多，能在 CPU/`mps` 上快速跑完）。

验证：loss 低于 M2；生成文本的局部连贯性应比 M2 更好（例如更像单词/短语）。

退出标准：能画出或口述一个 block 内部的数据流（输入 → LayerNorm → 多头注意力 → 残差 → LayerNorm → FFN → 残差 → 输出），并说明为什么需要残差连接。

## M4 — 采样策略、train/val 与收尾复盘

对应材料：nanoGPT 中 train/val 划分与 `generate` 里的 temperature/top-k 采样逻辑。

学习内容：train/val loss 分离、过拟合信号、`temperature` 和 `top-k` 对采样的影响、保存/加载 checkpoint。

练习：给 M3 的脚本加上验证集 loss 打印，并实现可调温度的采样，对比 temperature 从低到高时生成文本的变化。

验证：train/val loss 分别打印且可比较；至少用两个不同 temperature 生成文本并能描述差异。

退出标准：能解释 train/val 分离为什么必要、以及“temperature 越低越保守、越高越随机”背后的数学原因（对 logits 做缩放再 softmax）。

---

## 短期项目收尾

完成 M0-M4 即完整体验一次“最小但完整”的 LLM 流程。若之后想继续深入，下一周期可选择：换成 BPE/子词 tokenizer、对照完整 nanoGPT 做真实规模训练、或阅读一个开源小模型的训练脚本并写读书笔记——这些不在本次短期项目范围内。

## 进度状态

| 阶段 | 状态 | 首次开始 | 完成证据 | 下次复习 |
|---|---|---|---|---|
| M0 | 已完成 | 2026-09-06 | 拟合脚本 loss 36.08→0.011，`w=2.002, b=0.979`；独立正确复述 forward/backward/step/zero_grad 分工 | |
| M1 | 已完成 | 2026-09-06 | loss 4.51→~1.9（参考 ln(48)=3.87）；生成样例含真实词片段与常见字母组合；独立正确复述数据→tokenizer→模型→loss→生成全链路 | |
| M2 | 未开始 | | | |
| M3 | 未开始 | | | |
| M4 | 未开始 | | | |

## 暂不学习

在完成 M4 前，不把 BPE/子词分词、分布式或多 GPU 训练、指令微调/RLHF、模型量化部署、超参数大规模搜索作为本次短期项目的任务。它们值得学习，但会分散“最小完整流程”这一核心体验。
