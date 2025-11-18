#This Readme.md is crafted by Github Copilot… because I'm not a big fan of writing markdown.

# Parallel vs Sequential Merge Sort Benchmark

This project benchmarks a **parallel merge sort** using `std::thread` against a standard **sequential merge sort**.  
The goal is to measure the speedup achieved by using multithreading for different input sizes.

---

## Benchmark Setup

- **Language:** C++  
- **Multithreading:** `std::thread` (limited recursion depth to prevent thread explosion)  
- **Temporary array** used for merging (`temp`)  
- **Timer:** High-resolution clock (`std::chrono::high_resolution_clock`)  
- **Input:** Randomly generated integers of size `N`  

---

## Results

| N           | Multithread (ms) Run 1 | Run 2 | Run 3 | Sequential (ms) Run 1 | Run 2 | Run 3 |
|-------------|-----------------------|-------|-------|-----------------------|-------|-------|
| 10          | 0.1866                | 0.1608| 0.1581| 0.0034                | 0.0034| 0.0034|
| 100         | 0.2940                | 0.3345| 0.2810| 0.0333                | 0.0350| 0.0318|
| 1,000       | 0.3776                | 0.3468| 0.2865| 0.3557                | 0.3562| 0.3640|
| 10,000      | 1.1328                | 1.0146| 1.0903| 4.0326                | 3.6653| 3.8521|
| 100,000     | 10.2482               | 10.0653| 10.1267| 41.2992             | 41.3650| 42.5316|
| 1,000,000   | 94.1901               | 94.8962| 96.5182| 466.7100            | 464.059| 463.454|
| 10,000,000  | 996.209               | 958.524| 961.708| 5221.920            | 5235.330| 5211.880|

---

## Observations

1. For **small input sizes (N ≤ 1,000)**, the overhead of threads outweighs the benefit — sequential is faster.
2. For **medium to large input sizes (N ≥ 10,000)**, the parallel version provides significant speedup.
3. Maximum observed speedup is roughly **5x–6x** for `N = 10,000,000`.
4. Threading depth is limited to prevent excessive thread creation and stack overflow.

---

## Notes

- Make sure to compile with **C++11 or higher** (`-std=c++11` or `-std=c++17`).
- Use `std::ref` when passing vectors to threads to avoid unnecessary copies.
- The temporary array `temp` must be pre-allocated to prevent repeated allocations during merge.

---

## Example Compilation

```bash
clang++ -std=c++17 parallel_merge_sort.cpp -o parallel_merge_sort -pthread
./parallel_merge_sort
