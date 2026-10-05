/**
 * ============================================================================
 * Emergency Department Patient Triage & Sorting Analysis System
 * 
 * Author: Ajwel Janardhanan
 * Email: ajwelaj@gmail.com
 * Topic: Priority Queues (Max Heap), Heap Sort, and Quick Sort Benchmark
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PATIENTS 7

// Performance metrics container for tracking algorithm operations
typedef struct {
    int comparisons;
    int swaps;
} TriageMetrics;

// Reset operational metrics to zero
static void reset_metrics(TriageMetrics *m) {
    m->comparisons = 0;
    m->swaps = 0;
}

// Utility function to format and display array contents
static void display_scores(const int scores[], int len) {
    printf("[");
    for (int idx = 0; idx < len; idx++) {
        printf("%d%s", scores[idx], (idx < len - 1) ? ", " : "");
    }
    printf("]");
}

// Helper to swap two values in array and track swap count
static void perform_swap(int data[], int pos_a, int pos_b, TriageMetrics *m) {
    if (pos_a != pos_b) {
        int temp = data[pos_a];
        data[pos_a] = data[pos_b];
        data[pos_b] = temp;
        m->swaps++;
    }
}

// ============================================================================
// Part A: Max Heap Priority Queue Implementation
// ============================================================================

/**
 * Inserts a patient severity score into the Max Heap and bubbles up (sift-up)
 */
static void max_heap_insert(int heap[], int *current_size, int severity_score, TriageMetrics *m) {
    int idx = *current_size;
    heap[idx] = severity_score;
    (*current_size)++;

    while (idx > 0) {
        int parent_idx = (idx - 1) / 2;
        m->comparisons++;
        if (heap[parent_idx] >= heap[idx]) {
            break;
        }
        perform_swap(heap, parent_idx, idx, m);
        idx = parent_idx;
    }
}

// ============================================================================
// Part B: Heap Sort & Quick Sort Implementation
// ============================================================================

/**
 * Maintains the Max Heap property at a specified root index (sift-down)
 */
static void max_heapify(int data[], int heap_len, int root_idx, TriageMetrics *m) {
    while (true) {
        int highest = root_idx;
        int left_child = 2 * root_idx + 1;
        int right_child = 2 * root_idx + 2;

        if (left_child < heap_len) {
            m->comparisons++;
            if (data[left_child] > data[highest]) {
                highest = left_child;
            }
        }

        if (right_child < heap_len) {
            m->comparisons++;
            if (data[right_child] > data[highest]) {
                highest = right_child;
            }
        }

        if (highest == root_idx) {
            break;
        }

        perform_swap(data, root_idx, highest, m);
        root_idx = highest;
    }
}

/**
 * Heap Sort algorithm: bottom-up max heap construction followed by root extraction
 */
static void run_heap_sort(int scores[], int num_elements, TriageMetrics *m) {
    // Phase 1: Build Max Heap from bottom up
    for (int sub_root = num_elements / 2 - 1; sub_root >= 0; sub_root--) {
        max_heapify(scores, num_elements, sub_root, m);
        printf("Build at index %d: ", sub_root);
        display_scores(scores, num_elements);
        printf("\n");
    }
    printf("Heap building: %d comparisons, %d swaps\n", m->comparisons, m->swaps);

    // Phase 2: Extract maximum elements sequentially
    for (int active_size = num_elements - 1; active_size > 0; active_size--) {
        perform_swap(scores, 0, active_size, m);
        max_heapify(scores, active_size, 0, m);
        printf("Heap: ");
        display_scores(scores, active_size);
        printf(" | Sorted: ");
        display_scores(scores + active_size, num_elements - active_size);
        printf("\n");
    }
}

/**
 * Quick Sort algorithm using Lomuto partitioning strategy
 */
static void run_quick_sort(int scores[], int low_idx, int high_idx, int num_elements, TriageMetrics *m) {
    if (low_idx >= high_idx) {
        return;
    }

    int pivot_val = scores[high_idx];
    int partition_pos = low_idx;

    for (int scan_idx = low_idx; scan_idx < high_idx; scan_idx++) {
        m->comparisons++;
        if (scores[scan_idx] <= pivot_val) {
            perform_swap(scores, partition_pos, scan_idx, m);
            partition_pos++;
        }
    }
    perform_swap(scores, partition_pos, high_idx, m);

    printf("Range %d to %d, pivot %d, position %d: ", low_idx, high_idx, pivot_val, partition_pos);
    display_scores(scores, num_elements);
    printf("\n");

    run_quick_sort(scores, low_idx, partition_pos - 1, num_elements, m);
    run_quick_sort(scores, partition_pos + 1, high_idx, num_elements, m);
}

// ============================================================================
// Main Execution Entry Point
// ============================================================================

int main(void) {
    const int raw_dataset[MAX_PATIENTS] = {45, 72, 30, 90, 65, 50, 85};
    int priority_heap[MAX_PATIENTS];
    int heap_sort_buf[MAX_PATIENTS];
    int quick_sort_buf[MAX_PATIENTS];
    
    int heap_count = 0;
    TriageMetrics metrics;

    // Initialize algorithm data buffers
    for (int i = 0; i < MAX_PATIENTS; i++) {
        heap_sort_buf[i] = raw_dataset[i];
        quick_sort_buf[i] = raw_dataset[i];
    }

    printf("Patient severity scores: ");
    display_scores(raw_dataset, MAX_PATIENTS);
    printf("\n\nA) Max Heap Insertion\n");

    // Execute Part A: Dynamic Heap Insertion
    reset_metrics(&metrics);
    for (int i = 0; i < MAX_PATIENTS; i++) {
        max_heap_insert(priority_heap, &heap_count, raw_dataset[i], &metrics);
        printf("Insert %d: ", raw_dataset[i]);
        display_scores(priority_heap, heap_count);
        printf("\n");
    }
    printf("Comparisons: %d, Swaps: %d\n", metrics.comparisons, metrics.swaps);
    printf("Highest-priority patient: %d\n", priority_heap[0]);

    // Execute Part B.1: Heap Sort
    reset_metrics(&metrics);
    printf("\nB) Heap Sort\n");
    run_heap_sort(heap_sort_buf, MAX_PATIENTS, &metrics);
    printf("Comparisons: %d, Swaps: %d\n", metrics.comparisons, metrics.swaps);
    printf("Final output: ");
    display_scores(heap_sort_buf, MAX_PATIENTS);
    printf("\n");

    // Execute Part B.2: Quick Sort
    reset_metrics(&metrics);
    printf("\nB) Quick Sort\n");
    run_quick_sort(quick_sort_buf, 0, MAX_PATIENTS - 1, MAX_PATIENTS, &metrics);
    printf("Comparisons: %d, Swaps: %d\n", metrics.comparisons, metrics.swaps);
    printf("Final output: ");
    display_scores(quick_sort_buf, MAX_PATIENTS);
    printf("\n");

    return 0;
}
