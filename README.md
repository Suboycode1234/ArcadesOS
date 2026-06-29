# ArcadeOS 🎮 — Custom Kernel (Deprecated & Incomplete)

> [!WARNING]
> **DEPRECATED & INCOMPLETE:** This custom 32-bit x86 hobby kernel project is **incomplete** and is no longer in active use or development. It has been archived as a legacy learning project. The main active development of ArcadeOS has shifted to a custom, gaming-optimized Arch Linux distribution builder (available on the main `arch-distro` branch).

---


## 🚀 Features Implemented

* **Flat GDT (Global Descriptor Table)**: Loaded and activated with kernel code/data segments.
* **IDT (Interrupt Descriptor Table)**: Configured with 256 interrupt gates.
* **ISR (Interrupt Service Routines)**: Supports all 32 standard CPU exceptions with safe stack alignment.
* **PIC Remapping (Programmable Interrupt Controller)**: Cascaded 8259 PICs mapped to IRQ0–15 -> Vectors 32–47 with strict EOI (End of Interrupt) compliance.
* **System Timer (IRQ0)**: Verified ticking repeatedly.
* **Keyboard Driver (IRQ1)**: US QWERTY Set 1 translation, key-release filtering, and interactive typing support.
* **Modular VGA Driver**: Text rendering with scroll bounds checking, newline/backspace support.
* **Interactive Shell Input Buffer**: Staged line buffer (128-byte) with backspace/enter controls and string echoing.
* **Minimal Heap Allocator (`kmalloc`)**: Pointer-bump memory allocator with strict 4-byte size alignment and OOM panic handling.

---

## 🛠️ Requirements & Toolchain

To set up the development environment, compile the hobby kernel, or run it in emulation, you need to download and install the following tools:

### 🖥️ Core Virtualization & Emulation
*   **QEMU (Processor Emulator):** Needed to emulate and run the x86 custom kernel.
    *   🔗 [Download QEMU for Windows (64-bit)](https://www.qemu.org/download/#windows)
*   **i686-elf GCC Toolchain:** Cross-compiler toolchain needed to compile the 32-bit x86 target.
    *   🔗 [Prebuilt i686-elf-tools for Windows](https://github.com/lordmilko/i686-elf-tools)

### 🔧 Development Support Tools
*   **MSYS2 (Software Distribution and Building Platform):** Provides `make`, command line tools, and packages natively on Windows.
    *   🔗 [Download MSYS2 Installer](https://www.msys2.org/)

### 📝 Code Editor
*   **Visual Studio Code (VS Code):** Recommended editor for writing and reviewing C and Assembly source files.
    *   🔗 [Download Visual Studio Code](https://code.visualstudio.com/)

---

## ⚙️ How to Build & Run

Ensure your compiler tools and QEMU are added to your system path. Open **Git Bash** or your command line inside the project folder:

### 1. Compile the Kernel
```bash
make all
```
*Compiles assembly entry stubs, kernel source code, drivers, and links them into `kernel.elf`.*

### 2. Run in QEMU
```bash
make run
```
*Launches QEMU running your compiled kernel directly.*

### 3. Clean Build Artifacts
```bash
make clean
```
