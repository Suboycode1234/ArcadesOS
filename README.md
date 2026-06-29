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

### 🔍 Under the Hood: The Linux ISO Build Process
The build pipeline utilizes `mkarchiso` to package the live operating system. Understanding the stages of this process helps clarify how modifications propagate into the final ISO image:

1.  **Workspace Initial Staging (`~/archlive/`):**
    The configuration profile defines the package list (`packages.x86_64`), bootloader configurations (`efiboot/`, `syslinux/`, `grub/`), and target system file overrides (`airootfs/`).
2.  **Staging Environment Installation (`pacstrap`):**
    The builder runs `pacstrap` to construct a clean target root filesystem inside the WSL environment. It downloads and installs all specified packages into the working directory.
3.  **Kernel & Initramfs Generation:**
    Runs `mkinitcpio` within the pacstrap root to generate customized initial ramdisk images containing essential modules needed to mount the SquashFS filesystem at boot time.
4.  **Bootloader Configuration:**
    *   **BIOS (SYSLINUX):** Configures SYSLINUX for legacy system boots.
    *   **UEFI (systemd-boot):** Builds a standard FAT-formatted EFI system partition image containing systemd-boot.
5.  **Filesystem Compression (SquashFS):**
    Compresses the entire root filesystem into a highly compressed read-only SquashFS image (`airootfs.sfs`). This step is heavily multi-threaded (utilizing parallel processors) and represents the largest processing step.
6.  **ISO Image Final Packaging (`xorriso`):**
    Gathers the compressed SquashFS image, initramfs, kernel binaries, and bootloader images, compiling them into a final hybrid bootable ISO using `xorriso`.

### 🛠️ Script Architecture
*   **`install_wsl2.ps1`:** Runs on Windows to check for Administrator rights, enable the virtualization platforms, download WSL, set up WSL2, and register the Arch Linux VM.
*   **`run_install.ps1`:** Runs inside the WSL Arch Linux environment to download and install core packaging toolchains (`archiso`, `git`, `base-devel`) and clean up the pacman packages cache.
*   **`run_build.ps1`:** Coordinates the build pipeline, extracts progress indicators, serves the progress dashboard, and transfers the compiled ISO back to the Windows host.
*   **`progress.html`:** The HTML5 dynamic dashboard. It fetches progress updates and displays them in a sleek, dark-mode GUI showing elapsed time, overall percent bar, and active compiler stages.
*   **`launch_qemu.bat`:** Launches QEMU with Windows Hypervisor Platform (WHPX) acceleration. Runs as a scheduled task to bypass Windows Session 0 service isolation, displaying the GUI window directly in the user's active session.

---

## 🛠️ Prerequisites & Download Links

To set up the development environment, compile the hobby kernel, or build the Arch Linux distro, download and install the following tools:

### 🖥️ Core Virtualization & Emulation
*   **QEMU (Processor Emulator):** Needed to run both the custom x86 kernel and the compiled Arch Linux distro.
    *   🔗 [Download QEMU for Windows (64-bit)](https://www.qemu.org/download/#windows)
*   **WSL2 (Windows Subsystem for Linux):** Necessary for running the Arch Linux builder pipeline.
    *   🔗 [WSL installation guide & commands](https://learn.microsoft.com/en-us/windows/wsl/install)

### 🔧 Development Toolchains
*   **MSYS2 (Software Distribution and Building Platform):** Provides `make`, `gcc`, and packages to build tools natively on Windows.
    *   🔗 [Download MSYS2 Installer](https://www.msys2.org/)
*   **i686-elf GCC Toolchain:** Needed for cross-compiling the 32-bit x86 kernel track.
    *   🔗 [Prebuilt i686-elf-tools for Windows](https://github.com/lordmilko/i686-elf-tools)

### 📝 Editor
*   **Visual Studio Code (VS Code):** Recommended code editor for editing the kernel source and configuration profiles.
    *   🔗 [Download Visual Studio Code](https://code.visualstudio.com/)

---

## 🗺️ ArcadeOS Roadmap v5 — Gaming Linux Distribution

This roadmap supersedes the kernel-based roadmap (v0–v4). Previous custom kernel work has been archived as a separate completed learning project and is not a dependency for this distribution.

### ⚙️ Standing Rulings & Baseline
*   **Base OS:** Arch Linux, built via `archiso`.
*   **Target Experience:** Windows-style installer wizard, gaming-optimized defaults, and Wine/Proton pre-integrated.
*   **Engineering Discipline:** The strict **verify-before-proceed** discipline carries over unchanged from the kernel project. We inspect actual logs, file outputs, and boot menus at every single milestone.

### 🗺️ Phases of Development

#### 📦 PHASE 0 — Toolchain Setup (Completed)
*   [x] Install Arch-on-WSL2.
*   [x] Install `archiso` packaging toolchain.
*   [x] Automate the build process using custom monitoring scripts (`run_build.ps1`, `progress.html`).
*   [x] Compile and verify a baseline stock Arch ISO.
*   [x] Verify the live ISO successfully boots in QEMU with WHPX hardware acceleration on Windows.

#### 👥 PHASE 1 — Minimal Custom Profile (Next Phase)
*   Fork the default `releng` archiso profile configuration into your own custom profile (`arcadeos`).
*   Verify that your own custom profile name/structure compiles and boots successfully with **zero functional changes** first. This proves the customization pipeline itself is working before adding content.

#### 🐧 PHASE 2 — Base Package Set & Kernel Choice
*   Select a gaming-oriented performance kernel (e.g., `linux-zen` or `linux-cachyos` for lower latency scheduling).
*   Select the base desktop environment (KDE Plasma is recommended due to robust Wayland support, HDR development, and direct integration with gaming tools).
*   Add the packages and confirm the distro boots successfully to a desktop environment, rather than a minimal command shell.

#### 💿 PHASE 3 — Installer
*   Integrate the **Calamares** installer framework (used by user-friendly distros like EndeavourOS and Manjaro to provide a themeable, wizard-driven "Windows-style install" experience).
*   Create a virtual hard disk in QEMU and verify a real, permanent installation to disk works successfully (not just live-booting).

#### 🎮 PHASE 4 — Wine / Proton / Compatibility Layer Integration
*   Pre-bundle core translation layers: Wine, Proton-GE, and graphics libraries.
*   Pre-bundle or configure a graphical game manager (such as Steam, Lutris, Heroic Games Launcher, or a custom frontend).
*   Verify that an actual Windows game or executable launches and runs smoothly in the test environment.

#### ⚡ PHASE 5 — Gaming Optimizations
*   **GameMode:** Bundle and configure Feral Interactive's GameMode for CPU governor and process priority adjustments while playing.
*   **GPU Drivers:** Pre-configure native drivers (Mesa for AMD/Intel, NVIDIA proprietary drivers).
*   **Kernel Tweaks:** Apply performance scheduler parameters and memory swappiness optimizations (following a measure-before-tuning discipline).
*   **App & Emulator Bundling:** Pre-install popular gaming launchers, web browsers, engines, and emulators:
    *   *Launchers/Browsers:* Steam, Epic Games Launcher, Riot Games Installer, Chrome, Opera GX.
    *   *Game Engines:* Unity, Godot, Unreal Engine.
    *   *Emulators:* Vita3K (PS Vita), Xemu (Xbox), Citra/Azahar (3DS), and other popular emulation systems.
    *   *Optional:* Add an easy dualboot configuration mode (potentially bundled with Batocera).

#### 🎨 PHASE 6 — Desktop/Launcher Identity & Theming
*   Apply custom ArcadeOS desktop wallpapers, lock screens, system icons, and boot splash screens (`plymouth`).
*   Implement a dual-mode option: a full desktop environment interface vs. a steam-launcher-first console mode shell (`gamescope` session, similar to SteamOS).

#### 🛠️ PHASE 7 — Polish & Distribution
*   Define the official ISO packaging and distribution pipeline.
*   Develop an update/maintenance strategy for system packages.
*   Provide complete documentation and begin physical hardware testing outside of virtual QEMU emulators.

#### 🖥️ PHASE 8 — Windows-Style Installer Layout
*   Refine the Calamares installer themes to mimic a highly simplified, welcoming, and user-friendly "Windows-style" wizard interface for maximum accessibility.
