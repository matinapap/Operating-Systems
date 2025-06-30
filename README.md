# Operating Systems - Optional Assignment 2024–25  
**University of Piraeus – Department of Informatics**  

## Overview

This project consists of two separate C programs developed for the optional Operating Systems assignment. Each program demonstrates fundamental system programming concepts including process creation, inter-process synchronization, thread coordination, and concurrency control using POSIX primitives.

---

## Part 1 – Process Tree with `fork()` and `exec()`

This program creates a tree of 10 processes using the `fork()` system call, following a specific parent-child relationship (P0 → P1, P2, P3, etc.). Each process prints its name, PID, and PPID. The following synchronization constraints are implemented:

- **P2** waits for **P6** before printing its info.  
- **P3** waits for **P9** and one additional child before proceeding.  
- **P0** waits for **P1**, then replaces itself using `execlp()` to execute `cat` and print the source code.

### Key Concepts
- `fork()`, `wait()`, `waitpid()`, `execlp()`
- Process hierarchy and control flow
- Parent-child synchronization

---

## Part 2 – Thread Synchronization with POSIX Threads and Semaphores

This program launches **6 POSIX threads** executing two separate thread functions (`thread_func_1` and `thread_func_2`). Threads are divided into two groups:

- **Group 1:** Threads 0, 1, 2 → `thread_func_1`  
- **Group 2:** Threads 3, 4, 5 → `thread_func_2`

### Features

- **Semaphores** are used to strictly control the print order of messages, ensuring the output follows a specific sequence.
- **Mutexes** (`pthread_mutex_t`) protect three global counters (`counter`, `counter1`, `counter2`) to avoid race conditions.
- Each counter is incremented exactly **60,000,000** times across all threads.
- Final counter values are printed in `main()` after thread completion.

### Synchronization Tools Used

- `sem_init`, `sem_wait`, `sem_post`
- `pthread_create`, `pthread_join`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

---

## How to Compile

```bash
gcc -o process_tree process_tree.c
gcc -pthread -o thread_sync thread_sync.c

## How to Run

```bash
./process_tree
./thread_sync
