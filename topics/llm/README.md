# 最小 LLM 短期学习项目

一个短期项目：从零手写、体验一次最小但完整的 LLM 工作流——数据、字符级 tokenizer、模型、训练循环、采样生成——而不是调用现成的高层 API。当前进度与证据见 [learning/roadmap.md](learning/roadmap.md) 与 [learning/log.md](learning/log.md)。

## Start here

- 用 `$llm-coach` 进行本主题的引导式学习会话。
- 跨主题或只需要通用学习流程时，用通用的 `$learning-coach`。
- 每次只推进一个里程碑，练习放在 `exercises/<lesson>/` 下。

## 环境

- macOS（Apple Silicon, arm64），Python 3.14。
- 需要 `pip install torch`；训练脚本应优先尝试 `mps` 设备，不可用时回退 `cpu`。
- 不提交虚拟环境、模型 checkpoint 或大型数据集；语料保持在几 KB～几百 KB 量级，足够今天的最小闭环练习。

## 验证

每个里程碑的验证方式记录在 `learning/roadmap.md` 对应小节。典型形式：

```sh
python3 topics/llm/exercises/<lesson>/starter.py
```

将确切命令、打印出的 loss/生成样例摘要记录进学习日志。
