# 🏥 Hospital Patient Triage Priority Queue & Sorting Benchmark

**Author:** Ajwel Janardhanan (`ajwelaj@gmail.com`)  
**Course:** Data Structures & Algorithms Assignment  
**Language:** C (C11 standard)  

---

## 📌 Executive Summary

This project implements an automated **Emergency Department Patient Triage System** in C. Patient urgency is quantified using numerical severity scores (`45, 72, 30, 90, 65, 50, 85`), where a higher score indicates higher treatment priority.

The application evaluates three core data structure and algorithm approaches:
1. **Max Heap Priority Queue (Dynamic Insertion):** Maintains dynamic triage order with $O(1)$ access to the most critical patient.
2. **Heap Sort:** Constructs a max heap using bottom-up heapification and extracts elements sequentially.
3. **Quick Sort:** Sorts the severity array using Lomuto partition scheme with right-most pivot selection.

---

## 📋 Assignment Problem & Solution Matrix

| Assignment Question | Objective | Implementation & Deliverable |
| :--- | :--- | :--- |
| **Part (a)** | Implement Max Heap insertion for scores `[45, 72, 30, 90, 65, 50, 85]`. Display heap state after each insertion and report root node. | [`assignment.c`](assignment.c) (Section A)<br>[`triage_trace_analysis.md`](triage_trace_analysis.md) (Part A) |
| **Part (b)** | Implement Heap Sort & Quick Sort for the scores. Record intermediate partition/heapify steps and final sorted array. | [`assignment.c`](assignment.c) (Section B)<br>[`triage_trace_analysis.md`](triage_trace_analysis.md) (Part B) |
| **Part (c)** | Compare approaches based on tree structure/height, comparisons, swaps, time & space complexity. Select optimal design for continuous arrivals. | [`algorithm_benchmarks.md`](algorithm_benchmarks.md)<br>[`triage_system_design.md`](triage_system_design.md) |

---

## 📂 Repository File Architecture

```text
.
├── assignment.c              # Refactored C implementation (C11 standard, modular struct metrics)
├── input.txt                 # Input patient severity dataset reference
├── output.txt                # Exact terminal execution log
├── README.md                 # Project summary and documentation index
├── triage_trace_analysis.md  # Detailed step-by-step state transition tables & tree graphs
├── algorithm_benchmarks.md   # Mathematical complexity proofs & metric comparison table
└── triage_system_design.md   # Architectural conclusion & emergency triage system selection
```

---

## 💻 Build and Execution Instructions

### Prerequisites
- GCC or Clang compiler supporting `-std=c11`.

### Compilation & Execution (Linux / macOS)

```bash
gcc -std=c11 -Wall -Wextra -pedantic assignment.c -o assignment
./assignment
```

### Windows Compilation (PowerShell / MinGW / TCC)

```powershell
gcc -std=c11 -Wall -Wextra -pedantic assignment.c -o assignment.exe
.\assignment.exe
```

---

## 📊 Summary Benchmark Results

| Metric / Feature | Max Heap Priority Queue | Heap Sort | Quick Sort (Lomuto) |
| :--- | :---: | :---: | :---: |
| **Data Structure** | Array-backed Complete Binary Tree | Max Heap Array | Partitioned Array |
| **Max Tree Height ($h$)** | $2$ ($\lfloor \log_2 7 \rfloor$) | $2$ (Initial) | $O(\log n)$ avg recursion depth |
| **Observed Comparisons** | **9** | **21** (8 build + 13 extract) | **12** |
| **Observed Swaps** | **5** | **18** (4 build + 14 extract) | **6** |
| **Time Complexity (Worst)** | $O(\log n)$ insert / extract | $O(n \log n)$ guaranteed | $O(n^2)$ worst-case pivot |
| **Auxiliary Space** | $O(1)$ extra | $O(1)$ extra | $O(\log n)$ stack space |
| **Sorted Output** | N/A (Priority Queue) | `[30, 45, 50, 65, 72, 85, 90]` | `[30, 45, 50, 65, 72, 85, 90]` |

---

## 🏆 Key Architectural Recommendation

For real-time emergency triage with continuous patient arrivals:
- **Max Heap Priority Queue** is the optimal architecture.
- **Reasoning:** Emergency triage requires immediate $O(1)$ lookup of the single highest-priority patient (`heap[0] = 90`) and efficient $O(\log n)$ dynamic insertion when new patients arrive. Re-sorting the entire patient list using Heap Sort or Quick Sort ($O(n \log n)$ work) upon every arrival introduces unnecessary computational overhead.
