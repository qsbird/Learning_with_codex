# 学习档案

此文件帮助学习教练按你的目标和时间调整路线。第一次使用前填写；答案变化时更新。

- 目标：短期项目——体验一次最小但完整的 LLM 训练/生成闭环（数据 → tokenizer → 模型 → 训练 → 生成），从零手写理解每一步，而不是调用现成的高层 API。
- 当前经验：Python 有基础；深度学习与 PyTorch 是初学者，尚未写过张量、autograd 或训练循环。
- 每周时间：短期项目，今天约 2-4 小时用于第一阶段；预计再花 1-2 次同等时长的会话推进到迷你 GPT。
- 操作系统与环境：macOS（Apple Silicon, arm64），Python 3.14，尚未安装 PyTorch；训练设备优先尝试 `mps`，不可用则回退 `cpu`。
- 偏好的项目主题：字符级（char-level）语言模型，从零手写，路线参考 Andrej Karpathy 的 makemore / *Let's build GPT*。
- 当前阻塞：无 PyTorch 环境；张量、autograd、`nn.Module`、softmax/cross-entropy 等基础语法未学过，需要在首次遇到时讲解。

## 基线诊断

首次学习时，记录以下三项的结果：

1. `python3 -c "import torch; print(torch.__version__, torch.backends.mps.is_available())"`
2. 用 autograd 手动完成一次最小的 `loss.backward()` + `optimizer.step()`
3. 用自己的话解释“张量 → 前向 → loss → 反向传播 → 更新参数”这条链路

## 已检测环境

- 日期：2026-09-06
- Python：3.14.0
- 芯片：Apple Silicon（arm64）
- PyTorch：未安装（后续在 M0 安装并验证 `mps` 可用性）
- 仍待填写：M0 完成后的 PyTorch 版本、`mps` 可用性诊断结果。
