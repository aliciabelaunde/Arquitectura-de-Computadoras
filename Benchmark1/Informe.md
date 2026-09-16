### Phase 1: Environment Setup and Hardware Inspection

* Open the Linux terminal (Ubuntu/WSL2) and run 

```
lscpu | grep -E "L1|L2|L3|Model name"
```

 to inspect the cache hierarchy of the processor.


* Verify the exact L1 data cache line size by running 
```
getconf LEVEL1_DCACHE_LINESIZE
```


* Confirm the coherence block size by checking the kernel sysfs via
```
cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size
```


---

### Phase 2: Benchmark Code Implementation and Compilation

* Create the file `benchmark_arquitectura.c` in the Linux working directory and paste the complete source code provided in the guide.


* Compile the C code using the strict `-O1` flag to prevent compiler-driven loop reordering while maintaining deterministic measurements:
`gcc -Wall -Wextra -O1 benchmark_arquitectura.c -o benchmark_arquitectura -lm`.



---

### Phase 3: Execution and Performance Profiling

* Execute the compiled binary (`./benchmark_arquitectura`) to obtain execution times, GFLOPS, and Speedup metrics.


* Install the `perf` profiling tool if not already present (`sudo apt-get install -y linux-tools-generic linux-tools-common`).


* Profile hardware-level performance counters using `perf stat -e L1-dcache-loads,L1-dcache-load-misses,cycles,instructions ./benchmark_arquitectura` to evaluate L1 cache miss rates and Instructions Per Cycle (IPC).



---

### Phase 4: Data Tabulation and Report Generation

* Populate the performance template using empirical data gathered during execution:



| Phase / Configuration | Execution Time (s) | Performance (GFLOPS) | Speedup Factor | Cache Hit Rate |
| --- | --- | --- | --- | --- |
| **1. Naive (i-j-k)** | *[Measured]* | *[Calculated]* | 1.00x (Baseline) | Low (< 15%)

 |
| **2. Spatial Locality (i-k-j)** | *[Measured]* | *[Calculated]* | *[Calculated]* | High (> 90%)

 |
| **3. CPU Registers Utilization** | *[Measured]* | *[Calculated]* | *[Calculated]* | Optimal

 |
| **4. Loop Unrolling 4x (ILP)** | *[Measured]* | *[Calculated]* | *[Calculated]* | Maximum

 |

* Write rigorous technical responses for all four questionnaire items regarding cache line utilization, register retention, instruction-level parallelism, and checksum validation.


* Capture terminal screenshots displaying compilation output, program execution results, and `perf` metrics.

