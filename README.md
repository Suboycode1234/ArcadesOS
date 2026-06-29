# ArcadeOS 🎮 — Custom Kernel (Deprecated)

> [!WARNING]
> **DEPRECATED & ARCHIVED:** This custom 32-bit x86 hobby kernel project is no longer in active use or development. It has been archived as a completed learning project. The main active development of ArcadeOS has shifted to a custom, gaming-optimized Arch Linux distribution builder (available on the main `arch-distro` branch).

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

To build and run ArcadeOS, you need:

1. **i686-elf Toolchain**: Cross-compiler (`i686-elf-gcc`, `i686-elf-as`, `i686-elf-ld`).
2. **QEMU Emulator**: To emulate the x86 hardware environment.
3. **Make Utility**: To coordinate compilation.

### 📥 Downloading QEMU

* **Windows**:
  * [Official QEMU Windows Installer (64-bit)](https://www.qemu.org/download/#windows)
  * Alternative via MSYS2: `pacman -S mingw-w64-x86_64-qemu`
* **macOS**:
  * Install via Homebrew: `brew install qemu`
* **Linux (Ubuntu/Debian)**:
  * Install via APT: `sudo apt-get install qemu-system-x86`

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
