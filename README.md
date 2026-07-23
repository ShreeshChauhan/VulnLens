<div align="center">

# VulnLens

**Real-time vulnerability detection for C/C++ — with explanations, not just flags.**


</div>

---

VulnLens is a VS Code extension that analyzes C/C++ code as you write it and flags vulnerable patterns before they ship. Unlike static analyzers that give you a line number and a rule ID, VulnLens shows you *why* a pattern is dangerous — highlighting the specific code paths that triggered the prediction using a Grad-CAM heatmap over the underlying graph representation.

Under the hood it builds a Code Property Graph from your code, serializes it into a matrix representation, and classifies it with a CNN trained on real-world vulnerability data. The explainability layer maps the network's activations back to source lines so the highlight lands on the right code, not just the function.

---

## How it works

```
Your C/C++ code
      │
      ▼
 Joern (CPG extraction)
      │
      ▼
 CPG → N×N matrix
      │
      ▼
 CNN classifier  ──→  Grad-CAM activations
      │                        │
      ▼                        ▼
 Vulnerable / Safe    Line-level heat scores
                               │
                               ▼
                    VS Code diagnostic overlay
```

1. On file save, the extension sends your code to a local inference server
2. The server extracts a Code Property Graph using Joern
3. The CPG is serialized to a matrix (nodes as rows, edge structure encoded in columns)
4. A trained CNN classifies the matrix and Grad-CAM produces per-node activation scores
5. Node activations are mapped back to source line numbers via Joern's metadata
6. Flagged lines appear with squiggle underlines; hover for the confidence score and which graph nodes drove the prediction

---

## Results

| Metric | Score |
|--------|-------|
| F1 | — |
| Precision | — |
| Recall | — |
| Dataset | Big-Vul |

*Fill in after Week 2 training run.*

---

## Quickstart

### Prerequisites

- Python 3.9+
- Node.js 18+
- Java 11+ (required by Joern)
- VS Code

### 1. Install Joern

```bash
curl -L "https://github.com/joernio/joern/releases/latest/download/joern-install.sh" -o joern-install.sh
chmod +x joern-install.sh
./joern-install.sh
```

### 2. Set up the inference server

```bash
cd server
pip install -r requirements.txt
python main.py
# Server runs on localhost:8000
```

### 3. Install the extension

```bash
cd extension
npm install
npm run compile
```

Then open VS Code, press `F5` to launch the Extension Development Host, and open any `.c` or `.cpp` file.

### 4. Analyze

Save a C file — the extension sends it to the local server and underlines any flagged patterns. Hover over a flagged line to see the confidence score and a brief explanation of which code paths triggered the prediction.

---

## Project structure

```
vulnlens/
├── pipeline/          # CPG extraction and matrix serialization
├── model/             # CNN architecture, training, Grad-CAM
├── data/              # Dataset download and preprocessing scripts
├── server/            # FastAPI inference server
└── extension/         # VS Code extension (TypeScript)
```

---

## Limitations

- **C/C++ only** — the CPG extraction pipeline uses Joern's C frontend; other languages are not currently supported
- **Local inference only** — the model runs on your machine via a local server; there is no cloud backend
- **Joern parse failures** — Joern occasionally fails to parse heavily macro-expanded or non-standard C; the extension falls back silently in these cases
- **False positive rate** — like all learned classifiers, VulnLens will flag some safe code and miss some vulnerabilities; it is a signal, not a guarantee


---

## Built with

- [Joern](https://joern.io) — code property graph extraction
- [PyTorch](https://pytorch.org) — CNN training and inference
- [Captum](https://captum.ai) — Grad-CAM explainability
- [FastAPI](https://fastapi.tiangolo.com) — inference server
- [Big-Vul](https://github.com/ZeoVan/MSR_20_Code_vulnerability_Search_IntelliJ_Plugin) — vulnerability dataset
- VS Code Extension API

---

## License

MIT