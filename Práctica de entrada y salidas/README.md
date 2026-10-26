# ANSI C Laboratory: Isolated I/O, RAM FIFO Queue, and VRAM Display

This repository contains the full implementation of low-level drivers developed in **ANSI C (C89/C99)** for the Computer Architecture course[cite: 1]. The project models hardware-software interaction by simulating bus control signals, strict RAM memory management, memory-mapped video display (VRAM), and an integrated interactive terminal module with backspace support[cite: 1, 2].

## Project Overview

The primary goal of this laboratory is to implement low-level drivers simulating the behavior of a real system architecture[cite: 1]:

1. **Isolated I/O:** Simulates the `IO_READ` line on the control bus and the automatic handshake protocol resetting the status register after reading data[cite: 1].
2. **Circular FIFO Queue:** Manages intermediate RAM storage with explicit boundary handling (*Buffer Overflow* and empty queue detection) using modular arithmetic[cite: 1].
3. **VRAM Controller:** Maps a 4x4 screen matrix to physical memory and implements a vertical upward scroll function[cite: 1, 2].
4. **Integrator Terminal:** Decodes printable ASCII characters and handles visual deletion when receiving backspace codes (`0x08` / `0x7F`)[cite: 1, 2].


## Memory and Port Map

| Address / Port | Resource | System Function |
| :--- | :--- | :--- |
| `0x00` - `0x5F` | Code RAM | CPU executable instructions[cite: 1]. |
| `0x70` - `0x77` | Keyboard Queue | Circular FIFO RAM buffer (8 bytes)[cite: 1]. |
| `0x78`, `0x79`, `0x7A` | Queue Pointers | `0x78` = KB_HEAD \| `0x79` = KB_TAIL \| `0x7A` = KB_COUNT[cite: 1]. |
| `0xF0` - `0xFF` | VRAM (Monitor) | 4x4 Display Matrix (16 characters with latch)[cite: 1]. |
| Port `0x01` | Keyboard Status | Read/Status (Bit 0: Key ready)[cite: 1]. |
| Port `0x02` | Keyboard Data | Data (ASCII Character)[cite: 1]. |


## Repository Structure

```text
.
├── exp1_puerto_teclado.c      # Experiment 1: Isolated I/O and Handshake
├── exp2_cola_teclado.c        # Experiment 2: Circular FIFO buffer in RAM
├── exp3_vram_monitor.c        # Experiment 3: VRAM (4x4) and Vertical Scroll
├── reto_integrador_terminal.c # Integrator Challenge: Terminal with Backspace support
└── README.md                  # Project documentation

```

## Modules and Implementations

### Experiment 1: Port Reading (`exp1_puerto_teclado.c`)

Models `IO_READ` activation on the control bus. Reading from data port `0x02` automatically triggers a hardware handshake that resets `reg_status` back to `0`.

### Experiment 2: Circular FIFO Queue (`exp2_cola_teclado.c`)

Stores up to 8 bytes across RAM addresses `0x70..0x77`. Uses pointer registers stored directly in RAM addresses `0x78` (`KB_HEAD`), `0x79` (`KB_TAIL`), and `0x7A` (`KB_COUNT`) to handle buffer overflow and underflow conditions.

### Experiment 3: VRAM and Scroll (`exp3_vram_monitor.c`)

Maps a 4x4 display matrix to address range `0xF0..0xFF`. Implements `vram_scroll_arriba()`, shifting screen rows upward while blanking out the bottom line with space characters (`0x20`).

### Integrator Challenge: Terminal (`reto_integrador_terminal.c`)

Integrates keyboard capture from the FIFO queue directly to VRAM rendering. Intercepts Backspace characters (`0x08` / `0x7F`) to decrement the VRAM cursor position and erase characters dynamically.

## Compilation and Execution

Compile the source files using **GCC** with strict standard conformance flags (`-std=c99 -Wall -Wextra -pedantic`):

```bash
# Compile Experiment 1
gcc -std=c99 -Wall -Wextra -pedantic exp1_puerto_teclado.c -o exp1

# Compile Experiment 2
gcc -std=c99 -Wall -Wextra -pedantic exp2_cola_teclado.c -o exp2

# Compile Experiment 3
gcc -std=c99 -Wall -Wextra -pedantic exp3_vram_monitor.c -o exp3

# Compile Integrator Challenge Terminal
gcc -std=c99 -Wall -Wextra -pedantic reto_integrador_terminal.c -o terminal

```

Run any of the generated executables:

```bash
./exp1
./exp2
./exp3
./terminal

```

## Technical Requirements

* **Compiler:** GCC 4.8+ (C99 support required).
* **Environment:** Linux / WSL / macOS / MinGW on Windows.
* **Language Standard:** ANSI C (C89 / C99 strict).