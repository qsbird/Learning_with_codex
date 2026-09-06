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

### 2026-09-06 - M1: 最小闭环——字符级 bigram 语言模型

- 目标：手写字符级 bigram 模型，跑通"文本 → 词表/编码 → nn.Embedding 前向 → 交叉熵 loss → 训练循环 → 采样生成"的最小完整闭环。
- 学到了什么：`nn.Module`/`nn.Embedding` 的定义方式与 `super().__init__()` 的作用；`nn.Embedding` 按整数索引查表且保留原有维度、在末尾新增 embedding 维；分类任务用交叉熵而非 MSE，`ln(vocab_size)` 是"完全随机瞎猜"的熵上限（体检基线），不是像 M0 里 `w=2,b=1` 那样的"标准答案"；训练时的真实答案来自语料本身（`data[ix+1]`），生成时没有真实答案，只能按概率采样；`torch.multinomial` 采样与 `argmax` 贪心解码的区别（后者容易卡进重复循环）；`zero_grad()` 放在循环开头或结尾均可，关键约束是"每次 `backward()` 前 `.grad` 必须是干净的"。
- 疑问或误解：漏看 `nn.Embedding` 输出会保留原有维度（猜测 `(32,48)`，实际 `(32,1,48)`）；误判初始 loss 会"离参考值很远"（实际很接近，因为随机初始化本就接近均匀分布）；把 hint 注释里的变量名 `targets` 抄成变量名，产生 `NameError`（误判为 `AttributeError`）；复述全链路时两次漏掉环节（forward 打分步骤、生成采样步骤），并把 logits 与"概率"混用，经提示后自行补全并纠正术语。
- 练习：`topics/llm/exercises/m1-bigram/starter.py` 全部 6 个 TODO（词表/编码、`nn.Embedding` 模型、交叉熵、训练三步、生成采样）由学习者独立完成并修复了 1 个自造的变量名 bug。
- 证据：`python exercises/m1-bigram/starter.py` => `vocab size: 48`；初始 loss 4.51（参考 `ln(48)=3.87`）；训练 3000 步后 loss 降至约 1.9-2.0；生成样例包含真实语料片段（如 "Tomasoun"）与常见字母组合（"th"、"ing"），非随机字符。
- 能解释什么：完整、正确地口述了从语料到生成文本的六步链路；能区分训练阶段（有真实答案，用交叉熵）与生成阶段（无真实答案，用采样）；能区分 logits（原始打分）与概率（softmax 之后）。
- 下一步：M2，单头自注意力 + 因果 mask（在 M1 模型上扩展，替换 bigram 查表）。
