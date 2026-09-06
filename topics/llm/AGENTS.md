# LLM 主题规则

这些规则在仓库级学习工作区规则基础上，补充 `topics/llm/` 的专属约束。

- 每个练习自包含在 `exercises/<lesson>/` 下；语料放在该练习的 `data/` 子目录，保持在几百 KB 以内，不提交完整数据集或预训练权重。
- 生成的 checkpoint、日志、大体量生成样例写到 `out/llm/<lesson>/`，不要写进 `exercises/`。
- 训练设备通过一个小的选择函数决定（`mps` 可用则用 `mps`，否则 `cpu`），不要硬编码设备字符串。
- 按学习者选择的“从零手写”路线：先手写 tokenizer、attention、训练循环，再引入 `nn.MultiheadAttention`、`Trainer` 之类的高层封装做对照，不要一开始就用高层封装替代手写实现。
- 不提交 Python 虚拟环境目录；`requirements.txt` 只记录本主题练习需要的最小依赖（目前是 `torch`）。
