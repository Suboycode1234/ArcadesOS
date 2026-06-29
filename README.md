# ArcadeOS Distro Builder 🎮

ArcadeOS Distro Builder is a space-optimized WSL2 build pipeline that packages a custom, gaming-optimized Arch Linux live ISO using `archiso`.

---


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

To set up the environment and build/run the Arch Linux distribution, download and install the following tools:

### 🖥️ Core Virtualization & Emulation
*   **QEMU (Processor Emulator):** Needed to emulate and run the compiled Arch Linux distro.
    *   🔗 [Download QEMU for Windows (64-bit)](https://www.qemu.org/download/#windows)
*   **WSL2 (Windows Subsystem for Linux):** Necessary for running the Arch Linux builder pipeline.
    *   🔗 [WSL installation guide & commands](https://learn.microsoft.com/en-us/windows/wsl/install)

### 🔧 Development Support Tools
*   **MSYS2 (Software Development Environment):** Provides building blocks, scripting capabilities, and libraries natively on Windows.
    *   🔗 [Download MSYS2 Installer](https://www.msys2.org/)

### 📝 Code Editor
*   **Visual Studio Code (VS Code):** Recommended code editor for editing builder scripts and configuration profiles.
    *   🔗 [Download Visual Studio Code](https://code.visualstudio.com/)

---

## 🗺️ ArcadeOS Roadmap v6 — Gaming Linux Distribution + Dual Experience System

This roadmap supersedes the previous versions. The custom kernel track has been archived as a separate completed learning project and is not a dependency for this distribution.

### ⚙️ Standing Rulings & Baseline
*   **Base OS:** Arch Linux, built via `archiso`.
*   **Goal:** A gaming-focused Linux distribution that combines a full desktop gaming PC experience with a console-style gaming interface.
*   **Philosophy:** Verify every layer before building on top of it.
*   **Architecture:**
    ```text
    Arch Linux
        ↓
    Gaming-optimized system
        ↓
    ArcadeOS experience layer
        ↓
    Desktop Mode / Arcade Mode
    ```

### 🗺️ Phases of Development

#### 📦 PHASE 0 — Toolchain Setup ✅
*Goal: Prove the factory works before modifying the machine.*

*   **Tasks:**
    *   [x] Install Arch-on-WSL2.
    *   [x] Install `archiso` packaging toolchain.
    *   [x] Automate the build process using custom monitoring scripts (`run_build.ps1`, `progress.html`).
    *   [x] Compile and verify a baseline stock Arch ISO.
    *   [x] Verify the live ISO successfully boots in QEMU with WHPX hardware acceleration on Windows.

#### 👥 PHASE 1 — Custom ISO Profile 🔄 IN PROGRESS
*Goal: Create ArcadeOS itself, not just a modified Arch copy.*

*   **Tasks:**
    *   [x] Fork Arch `releng` profile.
    *   [x] Rename profile to ArcadeOS (`iso_name="arcadeos"`, `install_dir="arcade"`).
    *   [ ] Confirm custom ISO builds.
    *   [ ] Verify custom ISO boots in QEMU successfully. **<---- WE ARE HERE**

#### 🐧 PHASE 2 — Desktop Base + Gaming Stack
*Goal: Create the actual gaming desktop foundation.*

*   **Desktop:** KDE Plasma, Wayland, PipeWire audio, NetworkManager, Bluetooth support.
*   **Gaming Foundation:** Vulkan support, Mesa graphics stack, GPU detection, Controller support, GameMode, MangoHud, Gamescope.
*   **Kernel Evaluation:** Compare performance/latency of: `linux-zen`, `linux-cachyos`, and standard Arch kernel.
*   **Testing:** Desktop boots, graphics/audio/controller/Vulkan work.

#### 💿 PHASE 3 — Installer
*Goal: Make ArcadeOS install like a normal operating system.*

*   **Integrate:** Calamares installer.
*   **Features:** Disk selection, User creation, Language/timezone, Bootloader setup.
*   **Testing:**
    ```text
    ArcadeOS ISO ➔ QEMU virtual disk ➔ Install ➔ Restart ➔ Installed ArcadeOS boots
    ```
    *(The live environment is no longer the final product.)*

#### 🎮 PHASE 4 — Wine / Proton Compatibility Layer
*Goal: Make Windows games work easily.*

*   **Add:** Wine, Proton-GE, Wine-GE, DXVK, VKD3D-Proton, Winetricks, Lutris, Bottles.
*   **Integration:** Steam support, Epic Games / GOG support paths.
*   **Testing:** Run Windows games, launchers, and compatibility tools out of the box with zero manual Wine configuration required by the user.

#### ⚡ PHASE 5 — Gaming Optimizations + Drivers + Tools
*Goal: Make ArcadeOS feel tuned for gaming.*

*   **Hardware:** AMD, Intel, and NVIDIA graphics support (firmware packages).
*   **Optimization:** GameMode profiles, CPU scheduling tuning, power profiles, and background service control.
*   **Tools:** Steam, Heroic Games Launcher, Discord, Streaming & Recording tools.
*   **Development Tools (Optional Installers):** Unreal Engine, Unity, Godot.
*   **Emulation:** Preinstall: RetroArch, EmulationStation, Dolphin, PCSX2, PPSSPP, DuckStation, Vita3K, Xemu, and Citra/Azahar-style 3DS emulation.
*   **BIOS Handling:** Provide an **ArcadeOS Emulator Manager** interface (users place legally dumped BIOS files in `~/ArcadeOS/BIOS`).
*   *Optional:* Batocera-style emulator organization, dual-boot setup.

#### 🎨 PHASE 6 — Branding / Theme
*Goal: Make ArcadeOS recognizable.*

*   **Add:** ArcadeOS logo, boot animation, wallpapers, custom KDE theme, icons, and system sounds.
*   **Identity:** Establish a distinct identity: "ArcadeOS", not just "Arch with packages".

#### 🛠️ PHASE 7 — Polish / Distribution
*Goal: Turn the project into something people can actually use.*

*   **Add:** Update strategy, documentation, recovery options, bug reporting, and official release builds.
*   **Testing:** Test on physical desktop PCs, laptops, different GPUs, and maintain QEMU testing/reproducible builds.

#### 🖥️ PHASE 8 — Windows-Like Installation Experience
*Goal: Remove the Linux intimidation factor.*

*   **Improve Installer:** Simple language, clear choices, and automatic setup.
*   **First Boot Welcome Wizard:** Choose setup type (Gaming PC, Laptop, Living Room Console, Creator Machine) and apply automatic config (GPU, controller, recommended settings).

#### ⭐ PHASE 9 — ArcadeOS Dual Experience System
*Goal: Make one OS behave like both a PC and a console.*

*   **Core Architecture:**
    ```text
                  Boot
                    │
                    ▼
        ArcadeOS Experience Menu
        ┌──────────────────────┐
        ▼                      ▼
    Desktop Mode          Arcade Mode
    (KDE Plasma)          (Console UI)
    - Keyboard/mouse      - Gamepad controller
    - Full desktop        - Game launcher
    - Apps / Coding       - Emulation Station
    - Web Browsing        - Steam integration
    ```
*   **Mode Selection (At Boot):** Choose between 🖥️ Desktop Mode and 🎮 Arcade Mode, with customizable default startup preferences (Desktop, Arcade, or Ask every boot).
