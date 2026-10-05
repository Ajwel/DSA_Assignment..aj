# 📊 Algorithm Performance & Complexity Benchmarks

**Author:** Ajwel Janardhanan  
**Project:** Hospital Patient Priority Queue Benchmark  

This document provides a comprehensive theoretical and empirical comparison across all evaluated algorithms for the $n = 7$ patient dataset (`[45, 72, 30, 90, 65, 50, 85]`).

---

## 📈 Theoretical Complexity Matrix

| Operation / Algorithm | Best-Case Time | Average-Case Time | Worst-Case Time | Auxiliary Space |
| :--- | :---: | :---: | :---: | :---: |
| **Insert Patient into Max Heap** | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ |
| **Peek Highest Severity (Root)** | $O(1)$ | $O(1)$ | $O(1)$ | $O(1)$ |
| **Extract Highest Severity Patient** | $O(1)$ | $O(\log n)$ | $O(\log n)$ | $O(1)$ (iterative heapify) |
| **Build Max Heap (Bottom-Up Floyd)** | $O(n)$ | $O(n)$ | $O(n)$ | $O(1)$ |
| **Heap Sort (Distinct Keys)** | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(1)$ auxiliary |
| **Quick Sort (Lomuto Partition)** | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ avg stack, $O(n)$ worst |

---

## 🧮 Tree Structure & Mathematical Height Analysis

1. **Array Mapping:** A complete binary tree with $n$ nodes stored sequentially in array $A$:
   - Left Child of index $i$: $2i + 1$
   - Right Child of index $i$: $2i + 2$
   - Parent of index $i$: $\lfloor (i - 1) / 2 \rfloor$
2. **Tree Height Formula:**
   $$h = \lfloor \log_2 n \rfloor$$
   For $n = 7$ patients:
   $$h = \lfloor \log_2 7 \rfloor = 2$$
3. **Node Distribution per Level:**
   - **Level 0 (Root):** 1 node (`90`)
   - **Level 1:** 2 nodes (`72`, `85`)
   - **Level 2:** 4 nodes (`45`, `65`, `30`, `50`)

---

## 🔍 Metric Count Comparison (Observed Operations)

> **Metric Counting Methodology:**
> - **Comparisons:** Counts key comparison checks between severity scores ($A[i] > A[j]$). Loop bounds check and array index checks are excluded.
> - **Swaps:** Counts element exchanges between distinct array positions ($i \neq j$).

```text
Operation Comparisons & Swaps (n = 7 dataset)
===================================================
Max Heap Insertions : [ 9 Comparisons |  5 Swaps ]
Quick Sort (Lomuto) : [12 Comparisons |  6 Swaps ]
Heap Sort           : [21 Comparisons | 18 Swaps ]
```

### Analysis of Observed Counts
- **Quick Sort** used fewer comparisons (12) and swaps (6) than Heap Sort on this small, 7-element dataset because Lomuto partitioning required relatively few element exchanges on the initial array configuration.
- **Heap Sort** guarantees a strict upper bound of $O(n \log n)$ comparisons regardless of initial array ordering, making it immune to $O(n^2)$ worst-case degradation.
- **Max Heap Priority Queue** performs dynamic priority maintenance ($O(\log n)$ per insertion), which serves a different operational goal than full array sorting.
