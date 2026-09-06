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

### 2026-09-06 - M2: 单头自注意力 + 因果 mask

- 目标：在 M1 模型上加入位置编码、Q/K/V 单头自注意力与因果 mask，体验"能看一整个上下文窗口、动态算权重"的机制，对比 bigram 的固定查表。
- 学到了什么：位置编码（`nn.Embedding(block_size, n_embd)`）与 token embedding 相加、靠广播对齐的原理；`nn.Linear` 是可学习矩阵乘法；Q/K/V 三层结构相同但权重独立初始化、各自承担不同角色（提问/标签/内容）；`q@k^T` 缩放点积、`masked_fill`+`tril` 实现因果 mask、softmax 归一化为权重；`wei@v` 是按权重对 value 做加权平均；`exp`/softmax 的数学直觉；因果 mask 缺失会导致"信息泄漏/作弊"而非"死循环"——模型可直接抄下一个位置的输入当答案，训练 loss 骤降但生成时完全失效。
- 疑问或误解：把"query/key 各自需要独立参数"的原因说成"需要独立迭代"（同义反复,未讲出对称性问题），经对称性打分矩阵实测纠正；不理解"同一行代码 `nn.Linear(...)` 两次调用为何返回不同矩阵"，经打印实际权重数值纠正（每次构造都重新随机初始化）；对"第 0 个位置注意力权重分布"的描述把"1"和"0"的位置说反，经具体数字表纠正；把因果 mask 缺失的后果误判为"前后字符互相关注的死循环"，经对照实验（无 mask 训练 loss 崩到 0.18 vs 有 mask 的 ~2.0）纠正为"信息泄漏/作弊"；把 bigram 与自注意力的本质区别误归因于"新增位置矩阵"，经追问纠正为"能动态对多个位置算权重"这一核心机制。
- 练习：`topics/llm/exercises/m2-self-attention/starter.py` 全部 4 个 TODO（位置编码与合并、Q/K/V 投影、注意力打分/mask/softmax、加权聚合与投影）独立完成；手算 `softmax([1,3,2])≈[0.1,0.7,0.2]`，与 PyTorch 实际值 `[0.09,0.665,0.245]` 高度吻合。
- 证据：`python exercises/m2-self-attention/starter.py` => `vocab size: 48`；loss 3.94→1.87（M1 基线 1.92，参考 `ln(48)=3.87`）；生成样例出现大量完整真实单词（past、ten、ought、now、she、mouse）与正确的引号/大写句首结构，明显优于 M1 的碎片输出；额外对照实验验证了去掉因果 mask 会让训练 loss 骤降至 0.18（信息泄漏证据）。
- 能解释什么：能正确复述自注意力与 bigram 的本质区别在于"动态、可学习地对多个上下文位置算权重"（Q/K/V 机制），而非位置编码本身；能正确解释因果 mask 的必要性是防止训练/生成阶段信息不一致（而非"死循环"）；能手算并验证一次注意力权重的 softmax 计算。
- 下一步：M3，多头注意力 + Transformer block（迷你 GPT），在 M2 模型上扩展多头拼接、FFN、残差连接与 LayerNorm。
