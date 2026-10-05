# 🏛️ Hospital Emergency Department Triage System Design & Recommendation

**Author:** Ajwel Janardhanan  
**Project:** Hospital Patient Priority Queue Benchmark  

---

## 🎯 Problem Statement & Requirements

An Emergency Department (ED) requires a real-time patient triage management system. Incoming emergency patients are assigned numerical severity scores (`45, 72, 30, 90, 65, 50, 85`), where higher values indicate higher critical care priority.

The system must satisfy two core requirements:
1. **Continuous Patient Arrivals:** Patients arrive at unpredictable intervals throughout the day.
2. **Immediate Access to Critical Patient:** Attending physicians must instantly identify and treat the highest-severity patient available.

---

## ⚖️ Comparative Architectural Evaluation

### 1. Full Sorting Approach (Heap Sort / Quick Sort)
- **Workflow:** Store arriving patients in an un-ordered list. Re-run a full sorting algorithm whenever a physician requests the next patient or when new patients arrive.
- **Drawbacks:**
  - Full sorting requires $O(n \log n)$ time overhead per arrival.
  - Sorting orders the entire list from least severe to most severe, which computes unnecessary order relationships for low-priority patients who are not being treated next.
  - Quick Sort suffers from potential $O(n^2)$ worst-case degradation if incoming arrivals exhibit sorted or near-sorted trends.

### 2. Max Heap Priority Queue Approach
- **Workflow:** Maintain a binary Max Heap where array root `heap[0]` always holds the highest severity score.
- **Advantages:**
  - **$O(1)$ Instant Top Access:** The highest severity patient is always at index `0`. No search or sorting is required before treating a critical patient.
  - **$O(\log n)$ Dynamic Insertions:** Inserting a newly arrived emergency patient takes at most $\lfloor \log_2 n \rfloor$ swaps to restore priority order.
  - **$O(\log n)$ Dequeue Operation:** Removing the treated top patient and updating the queue takes $O(\log n)$ sift-down work.
  - **Minimal Memory Overhead:** Stored in a contiguous array without pointers or call stack overhead.

---

## 🏁 Final System Decision

```text
================================================================================
RECOMMENDED ARCHITECTURE: Max Heap Priority Queue
================================================================================
  - Top Severity Retrieval : O(1) Instant
  - Dynamic Patient Arrival: O(log n) Sift-Up
  - Patient Dequeue (Treated): O(log n) Sift-Down
  - Space Overhead         : O(1) Auxiliary
================================================================================
```

**Conclusion:**  
A **Max Heap Priority Queue** is unequivocally the superior algorithm choice for emergency hospital patient triage. It directly aligns with the operational workflows of emergency medical care by providing instant $O(1)$ access to the most critical patient while minimizing dynamic update overhead to $O(\log n)$.
