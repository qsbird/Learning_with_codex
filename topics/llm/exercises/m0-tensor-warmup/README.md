# M0 — 张量与 autograd 热身

对应 `topics/llm/learning/roadmap.md` 的 M0。先读该文件的 M0 小节，再动手。

## 任务

用手写的线性模型 `pred = w * x + b`（**不用** `nn.Linear`）和 `torch.optim.SGD`，拟合一批满足 `y = 2x + 1`（外加一点噪声）的数据点。

`starter.py` 已经准备好：

- 数据生成（`x`, `y`）；
- 设备选择函数 `pick_device()`（`mps` 可用则用 `mps`，否则 `cpu`）；
- 训练循环的骨架，标了 `# TODO` 的地方需要你填。

## 需要你填的部分（`starter.py` 里的 TODO）

1. 用 `requires_grad=True` 创建 `w`、`b` 两个标量张量参数。
2. 写出前向计算 `pred = w * x + b`。
3. 用均方误差写出 `loss`。
4. 补上训练循环里的 `loss.backward()`、`optimizer.step()`、`optimizer.zero_grad()`，并想清楚这三行谁先谁后、为什么。

## 验证

```sh
pip install -r ../../requirements.txt   # 或在仓库根目录: pip install -r topics/llm/requirements.txt
python3 starter.py
```

期望看到：打印出的 loss 逐步下降到接近 0；脚本开头打印出实际选择的设备（`mps` 或 `cpu`）。

## 完成后

能不看代码，口头解释一次训练迭代里 `backward()`、`step()`、`zero_grad()` 各自的作用与固定顺序，再去更新 `topics/llm/learning/roadmap.md` 的 M0 状态和 `learning/log.md`。
