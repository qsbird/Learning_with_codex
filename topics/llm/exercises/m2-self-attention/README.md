# M2 — 单头自注意力 + 因果 mask

对应 `topics/llm/learning/roadmap.md` 的 M2。这一课在 M1 的字符级模型基础上加入自注意力，让模型能看到不止"前一个字符"。

先完成 M0、M1，再做这一课。

## 和 M1 的区别

M1 的 bigram 模型只看得到当前这一个字符（`block_size` 相当于 1）。M2 引入**上下文窗口**（`BLOCK_SIZE = 16`）：模型每次能看到最近 16 个字符，并且用自注意力机制决定"这 16 个字符里，哪些对预测下一个字符更重要"。

数据加载（`get_batch`）、训练循环、生成函数（`generate`）都已经帮你写好——它们是 M0/M1 已经练过的模式（只是窗口从 1 个字符变成 16 个），不重复练。这一课只留自注意力本身的 4 个 TODO。

## 语料

复用 M1 的 `../m1-bigram/data/corpus.txt`，不用另外准备。

## 需要你填的部分（`starter.py` 里的 TODO）

1. **TODO 1**：位置编码（position embedding）表的创建，以及和 token embedding 相加。
2. **TODO 2**：Query/Key/Value 三个线性投影层的创建，以及在 `forward` 里用它们算出 `q`、`k`、`v`。
3. **TODO 3**：算注意力打分——缩放点积、因果 mask、softmax。
4. **TODO 4**：用注意力权重混合 value，再投影成词表大小的 logits。

每个 TODO 都在教练的引导下逐步完成，不用自己翻资料现推公式。

## 验证

```sh
cd "topics/llm"
source .venv/bin/activate
python exercises/m2-self-attention/starter.py
```

期望看到：

- loss 应该比 M1 的 bigram 基线（最终 ~1.9-2.0）更低，因为模型现在能利用更多上下文；
- 生成文本的局部片段应该比 M1 更像真实词汇。

## 完成后

能解释"为什么 bigram 只看得到前一个字符，自注意力能看到更早的上下文"，以及因果 mask 为什么必须存在；能对一个 4-5 个字符的小例子手算一次注意力权重。把解释、验证命令和输出摘要记进 `topics/llm/learning/log.md`，并更新 `learning/roadmap.md` 里 M2 的状态。
