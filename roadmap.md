# 📜 ArcadeOS Roadmap v6 — Gaming Linux Distribution + Dual Experience System

This roadmap supersedes the previous versions. The custom kernel track has been archived as a separate completed learning project and is not a dependency for this distribution.

---

## ⚙️ Standing Rulings & Baseline
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

---

## 🗺️ Phases of Development

### 📦 PHASE 0 — Toolchain Setup ✅
*Goal: Prove the factory works before modifying the machine.*

*   **Setup:**
    *   Arch Linux build environment.
    *   WSL2 development environment (configured with mirrored networking & DNS tunneling).
    *   `archiso` installed.
    *   Required build tools installed.
    *   QEMU testing environment (WHPX acceleration, Session 1 GUI bypass).
*   **Tasks:**
    *   [x] Build stock Arch ISO.
    *   [x] Boot stock ISO in QEMU.
    *   [x] Confirm `archiso` pipeline works.
    *   [x] Confirm ISO generation is repeatable.
*   **Success Condition:**
    ```text
    Source files ➔ mkarchiso ➔ ISO ➔ QEMU boot (No customization yet)
    ```

### 👥 PHASE 1 — Custom ISO Profile 🔄 IN PROGRESS
*Goal: Create ArcadeOS itself, not just a modified Arch copy.*

*   **Tasks:**
    *   [x] Fork Arch `releng` profile.
    *   [x] Rename profile to ArcadeOS (`iso_name="arcadeos"`, `install_dir="arcade"`).
    *   [ ] Confirm custom ISO builds.
    *   [ ] Verify custom ISO boots in QEMU successfully.
*   **Testing:**
    ```text
    ArcadeOS ISO ➔ QEMU ➔ Boot successful (No major features yet)
    ```
*   **Purpose:** Prove the customization pipeline before adding complexity. **<---- WE ARE HERE**

### 🐧 PHASE 2 — Desktop Base + Gaming Stack
*Goal: Create the actual gaming desktop foundation.*

*   **Desktop:**
    *   KDE Plasma.
    *   Wayland.
    *   PipeWire audio.
    *   NetworkManager.
    *   Bluetooth support.
*   **Gaming Foundation:**
    *   Vulkan support.
    *   Mesa graphics stack.
    *   GPU detection.
    *   Controller support.
    *   GameMode.
    *   MangoHud.
    *   Gamescope.
*   **Kernel Evaluation:**
    *   Compare performance/latency of: `linux-zen`, `linux-cachyos`, and standard Arch kernel.
*   **Testing:**
    *   Desktop boots, graphics/audio/controller/Vulkan work.

### 💿 PHASE 3 — Installer
*Goal: Make ArcadeOS install like a normal operating system.*

*   **Integrate:**
    *   Calamares installer.
*   **Features:**
    *   Disk selection.
    *   User creation.
    *   Language/timezone.
    *   Bootloader setup.
*   **Testing:**
    ```text
    ArcadeOS ISO ➔ QEMU virtual disk ➔ Install ➔ Restart ➔ Installed ArcadeOS boots
    ```
    *(The live environment is no longer the final product.)*

### 🎮 PHASE 4 — Wine / Proton Compatibility Layer
*Goal: Make Windows games work easily.*

*   **Add:**
    *   Wine, Proton-GE, Wine-GE, DXVK, VKD3D-Proton.
    *   Winetricks, Lutris, Bottles.
*   **Integration:**
    *   Steam support.
    *   Epic Games / GOG support paths.
*   **Testing:**
    *   Run Windows games, launchers, and compatibility tools out of the box with zero manual Wine configuration required by the user.

### ⚡ PHASE 5 — Gaming Optimizations + Drivers + Tools
*Goal: Make ArcadeOS feel tuned for gaming.*

*   **Hardware:**
    *   AMD, Intel, and NVIDIA graphics support (firmware packages).
*   **Optimization:**
    *   GameMode profiles, CPU scheduling tuning, power profiles, and background service control.
*   **Tools:**
    *   Steam, Heroic Games Launcher, Discord, Streaming & Recording tools.
*   **Development Tools (Optional Installers):**
    *   Unreal Engine, Unity, Godot.
*   **Emulation:**
    *   Preinstall: RetroArch, EmulationStation, Dolphin, PCSX2, PPSSPP, DuckStation, Vita3K, Xemu, and Citra/Azahar-style 3DS emulation.
*   **BIOS Handling (Do not ship copyrighted BIOS files):**
    *   Provide an **ArcadeOS Emulator Manager** interface.
    *   Users place legally dumped BIOS files in: `~/ArcadeOS/BIOS`.
    *   *Optional:* Batocera-style emulator organization, dual-boot setup.

### 🎨 PHASE 6 — Branding / Theme
*Goal: Make ArcadeOS recognizable.*

*   **Add:**
    *   ArcadeOS logo, boot animation, wallpapers, custom KDE theme, icons, and system sounds.
*   **Identity:**
    *   Establish a distinct identity: "ArcadeOS", not just "Arch with packages".

### 🛠️ PHASE 7 — Polish / Distribution
*Goal: Turn the project into something people can actually use.*

*   **Add:**
    *   Update strategy, documentation, recovery options, bug reporting, and official release builds.
*   **Testing:**
    *   Test on physical desktop PCs, laptops, and different GPUs.
    *   Maintain QEMU testing and reproducible builds.

### 🖥️ PHASE 8 — Windows-Like Installation Experience
*Goal: Remove the Linux intimidation factor.*

*   **Improve Installer:**
    *   Simple language, clear choices, and automatic setup.
*   **First Boot Welcome Wizard:**
    ```text
    Welcome to ArcadeOS 🎮
    Choose your setup:
    ○ Gaming PC    ○ Laptop    ○ Living Room Console    ○ Creator Machine
    ```
*   **Automatic Configuration:**
    *   GPU setup, controller setup, gaming packages, and recommended settings applied based on wizard choice.

### ⭐ PHASE 9 — ArcadeOS Dual Experience System
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
*   **Mode Selection (At Boot):**
    ```text
    Welcome to ArcadeOS
    Choose:
    🖥️ Desktop Mode
    🎮 Arcade Mode
    [ENTER]
    ```
*   **Default Startup Settings:**
    *   ○ Desktop  ○ Arcade  ○ Ask every boot
