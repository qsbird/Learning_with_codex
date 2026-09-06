# 学习日志

追加式记录：每次完成一个里程碑后在末尾新增一条。

```md
### YYYY-MM-DD - M<N>: <主题>

- 目标：
- 学到了什么：
- 疑问或误解：
- 练习：
- 证据：`<命令>` => <结果>
- 能解释什么：
- 下一步：
```

### 2026-09-06 - M0: 张量与 autograd 热身

- 目标：手写 `pred = w*x + b` + SGD，拟合 `y = 2x + 1`（带噪声），体验 forward/backward/optimizer 的完整闭环。
- 学到了什么：`requires_grad=True` 只开启梯度追踪，`.grad` 在 `backward()` 之前是 `None`；不同 device（`cpu`/`mps`）的张量不能直接运算；广播规则按逐维比较、`1` 的维度补齐；`.grad` 默认累加，不清零会导致训练发散。
- 疑问或误解：一开始漏写 `device=device`；对"猜对时 loss 是否为 0"的预测忽略了噪声带来的不可约误差；对去掉 `zero_grad()` 后果的预测（"不好判断"）过于保守，实测是明显发散/震荡，而非难以判断。
- 练习：`topics/llm/exercises/m0-tensor-warmup/starter.py` 的 4 个 TODO（张量创建、前向计算、MSE loss、backward/step/zero_grad）均由学习者独立完成，教练仅在漏 `device` 参数和 `zero_grad()` 预测环节给出针对性纠正。
- 证据：`python exercises/m0-tensor-warmup/starter.py` => loss 从 36.08 降到 0.011，`learned w=2.002, b=0.979`（目标 `w=2.0, b=1.0`）；`torch.backends.mps.is_available()` 为 `True`，脚本实际用 `mps` 训练成功。
- 能解释什么：能独立、正确地口述 forward → loss → backward → step → zero_grad 五步的因果顺序与各自职责，并在教练追问下修正了"backward 是为下一轮还是这一轮准备梯度"的措辞。
- 下一步：M1，字符级 bigram 语言模型（`topics/llm/exercises/m1-bigram/`）。
