# ArcadeOS 🎮

ArcadeOS is a dual-track operating system development project aiming to create a gaming-focused OS environment. The repository consists of two components:

1.  **ArcadeOS Kernel:** A multiboot-compatible, 32-bit x86 hobby operating system designed to run bare-metal or in an emulator.
2.  **ArcadeOS Distro Builder:** A space-optimized WSL2 build pipeline that packages a custom, gaming-optimized Arch Linux live ISO.

---

## 💻 Track 1: ArcadeOS x86 Hobby Kernel

### 🚀 Features Implemented
*   **Flat GDT (Global Descriptor Table)**: Loaded and activated with kernel code/data segments.
*   **IDT (Interrupt Descriptor Table)**: Configured with 256 interrupt gates.
*   **ISR (Interrupt Service Routines)**: Supports all 32 standard CPU exceptions with safe stack alignment.
*   **PIC Remapping (Programmable Interrupt Controller)**: Cascaded 8259 PICs mapped to IRQ0–15 -> Vectors 32–47.
*   **Drivers:** System Timer (IRQ0), Keyboard Driver (IRQ1) with US QWERTY Set 1 translation, and a modular VGA driver with scrolling/text rendering support.
*   **Interactive Shell Input Buffer**: Staged 128-byte line buffer with backspace/enter controls and command echoing.
*   **Memory Management:** Minimal Heap Allocator (`kmalloc`) with bump allocation and paging/physical memory management foundation.

### ⚙️ How to Build & Run
Ensure your compiler tools (`i686-elf-gcc`, `i686-elf-as`, `i686-elf-ld`) and QEMU are added to your system path.
```bash
# Compile assembly entry stubs, kernel source code, drivers, and link them
make all

# Launch QEMU running the compiled kernel directly
make run

# Clean build artifacts
make clean
```

---

## 💿 Track 2: ArcadeOS Arch Linux Distro Builder

A fully automated, space-optimized build environment configured inside WSL2 (Arch Linux distro) to generate a bootable Arch-based gaming ISO using `archiso`.

### 🚀 Features Implemented
*   **Space-Optimized WSL Setup:** Automated cleanups of pacman package download caches to remain well within tight disk constraints.
*   **PowerShell Automation (`run_build.ps1`):** Orchestrates the `mkarchiso` build stages, extracts status lines in real-time, and transfers the compiled ISO back to the Windows host (`C:\Users\sethj\ArcadeOS-distro\`).
*   **Real-time Progress Dashboard (`progress.html`):** A modern, dark-themed local webpage serving real-time logs, completion percentages, active stages (Setup, Pacstrap, Initramfs, Bootloader, SquashFS, ISO packaging), and celebration states. Runs on local HTTP server (`localhost:7890`).
*   **Safe Post-Build Cleanup:** Automatically purges intermediate files from WSL `/tmp/` and the archlive working directories after completing the Windows transfer.
*   **Detached QEMU Boot Launcher:** Bypasses Session 0 service isolation to trigger an interactive QEMU window with hardware acceleration (WHPX) in the user's active session.

### ⚙️ How to Build & Run
1.  **Open PowerShell** inside the project root directory.
2.  **Start the Build script:**
    ```powershell
    .\run_build.ps1
    ```
3.  **View Progress:**
    Open the live progress webpage in your browser:
    ```
    http://localhost:7890/progress.html
    ```
4.  **Boot Test in QEMU:**
    Once the build completes (100%), run the boot test to verify the ISO:
    ```powershell
    # Launcher batch file helper
    .\launch_qemu.bat
    ```
