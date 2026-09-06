# M1 — 最小闭环：字符级 bigram 语言模型

对应 `topics/llm/learning/roadmap.md` 的 M1。这是今天短期项目的主目标：跑通一次“数据 → tokenizer → 模型 → 训练 → 生成”的完整最小闭环。

先完成 M0，再做这一课。

## 语料

`data/corpus.txt` 是一段原创的小短文（几 KB），字符种类足够训练一个字符级 bigram 模型。你也可以之后换成更大的语料（例如 tiny-shakespeare），但今天先用这个小文件，保证几秒内能跑完一轮训练。

## 任务

在 `starter.py` 中实现一个字符级 bigram 语言模型：给定当前一个字符，预测下一个字符最可能是什么。

`starter.py` 已经准备好：

- 读取语料、设备选择（复用 M0 的思路）；
- 训练循环与生成函数的骨架，标了 `# TODO` 的地方需要你填。

## 需要你填的部分（`starter.py` 里的 TODO）

1. 从语料构建字符词表 `chars`，以及 `stoi` / `itos` 两个映射。
2. 把整段语料编码成一个整数张量。
3. 用 `nn.Embedding(vocab_size, vocab_size)` 作为 bigram 查表模型，写出 `forward`：输入一批字符 id，输出下一个字符的 logits。
4. 用 `F.cross_entropy` 计算 loss。
5. 补上训练循环里的 `backward` / `step` / `zero_grad`。
6. 实现 `generate`：从一个起始字符开始，重复“模型给出下一个字符的概率分布 → `torch.multinomial` 采样 → 拼接”，生成一段文本。

## 验证

```sh
python3 starter.py
```

期望看到：

- 训练开始时打印的初始 loss，应接近 `ln(vocab_size)`（脚本会打印这个参考值）；
- 训练若干步后 loss 明显下降；
- 结尾打印一段生成文本（质量会很差，很多不是真实单词，这是预期的——bigram 模型只看得到前一个字符）。

## 完成后

不看代码，口头/书面描述一次完整链路：原始文本 → 字符词表 → 编码成整数张量 → embedding 查表得到 logits → cross-entropy → backward → 用模型采样生成文本。把这段解释、验证命令和输出摘要记进 `topics/llm/learning/log.md`，并把 `learning/roadmap.md` 里 M0、M1 的状态更新为已完成。
