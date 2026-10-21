# Implementation and Benchmarking of Communication Bus & IPC Optimization in Linux (Zero-Copy vs FIFO)

## Overview
This project evaluates the performance impact of system call (syscall) overhead and User-Space to Kernel-Space memory copies in Linux inter-process communication (IPC). 

We implement and compare two Producer-Consumer models transferring **10,000,000 packets** (64 bytes each):
1. **Non-Optimized Approach**: Uses Named Pipes (FIFO) requiring 20,000,000 syscalls (`read`/`write`).
2. **Optimized Approach**: Uses POSIX Shared Memory (`mmap`), Ring Buffer, POSIX Semaphores, and Batching (500 packets per batch), reducing system calls by 99.8%.


## Technical Comparison

| Feature / Metric | Non-Optimized (FIFO) | Optimized (Zero-Copy SHM) | Performance Gain |
| :--- | :--- | :--- | :--- |
| **IPC Mechanism** | Named Pipe (`/tmp/bus_fifo_no_opt`) | Shared Memory (`/bus_shm_opt`) | Direct RAM Access |
| **System Calls** | 20,000,000 (`read`/`write`) | ~40,000 (Semaphore Signals) | **99.8% Reduction** |
| **Data Transfer** | Copy between User & Kernel Space | Zero-Copy via `mmap` | No Kernel Overhead |
| **Sync Strategy** | Blocking Pipe I/O | POSIX Semaphores + Batching (500 pkts) | High CPU Density |
| **Expected Time** | ~8.0 - 15.0 seconds | ~0.15 - 0.40 seconds | **30x - 50x Faster** |
| **Expected PPS** | ~800k - 1.2M packets/sec | ~25M - 50M packets/sec | Massively Increased |
| **Throughput** | ~50 - 80 MB/s | ~1,500 - 3,000 MB/s | Full RAM Bus Utilization |

## Project Structure

```text
├── Prod_NO.c      # Non-optimized producer (FIFO/Pipe)
├── Cons_NO.c      # Non-optimized consumer (FIFO/Pipe)
├── Prod_OPT.c     # Optimized producer (Shared Memory + Batching)
├── Cons_OPT.c     # Optimized consumer (Shared Memory + Batching)
└── README.md      # Project documentation & benchmark report

```

## Requirements & Environment

* **OS**: Linux (Ubuntu 20.04/22.04 LTS or WSL2)
* **Compiler**: `gcc` (with support for C99 or later)
* **Libraries**: POSIX Realtime (`-lrt`) and POSIX Threads (`-lpthread`)

## Instructions

### 1. Compilation

Compile:

```bash
# Compile Non-Optimized Programs
gcc -O3 Prod_NO.c -o Prod_NO
gcc -O3 Cons_NO.c -o Cons_NO

# Compile Optimized Programs (Requires POSIX Libraries)
gcc -O3 Prod_OPT.c -o Prod_OPT -lrt -lpthread
gcc -O3 Cons_OPT.c -o Cons_OPT -lrt -lpthread

```

### 2. Running Benchmarks

#### **Test 1: Non-Optimized Version (FIFO)**

Run both consumer and producer processes in parallel:

```bash
./Cons_NO & ./Prod_NO

```

#### **Test 2: Optimized Version (Zero-Copy Shared Memory)**

Run both optimized consumer and producer processes in parallel:

```bash
./Prod_OPT & ./Cons_OPT

```

## Experimental Results & Screenshots

### 1. Compilation


*Figure 1: Successful compilation of all four C source files with `-O3` optimization.*


### 2. Non-Optimized Execution (FIFO / Named Pipe)


*Figure 2: Terminal output for `Cons_NO` and `Prod_NO` showing total execution time, PPS, and MB/s.*


### 3. Optimized Execution (POSIX SHM Zero-Copy)


*Figure 3: Terminal output for `Cons_OPT` and `Prod_OPT` showing accelerated execution metrics.*

## Experimental Summary

| Execution Run | Process | Total Packets | Time Elapsed (s) | Speed (PPS) | Throughput (MB/s) |
| --- | --- | --- | --- | --- | --- |
| **Non-Optimized** | Producer (`Prod_NO`) | 10,000,000 | *[Your Time]* | *[Your PPS]* | *[Your MB/s]* |
| **Non-Optimized** | Consumer (`Cons_NO`) | 10,000,000 | *[Your Time]* | *[Your PPS]* | *[Your MB/s]* |
| **Optimized** | Producer (`Prod_OPT`) | 10,000,000 | *[Your Time]* | *[Your PPS]* | *[Your MB/s]* |
| **Optimized** | Consumer (`Cons_OPT`) | 10,000,000 | *[Your Time]* | *[Your PPS]* | *[Your MB/s]* |

## Authors & Credits

* **Requester:** Eng. Paulo César Loayza
* **Assignee:** Maria Alicia Belaunde Villagomez
* **Date:** September 2026

```
