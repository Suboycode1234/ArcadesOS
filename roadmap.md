# 📜 ArcadeOS Roadmap v5 — Gaming Linux Distribution

This roadmap supersedes the kernel-based roadmap (v0–v4). Previous custom kernel work has been archived as a separate completed learning project and is not a dependency for this distribution.

---

## ⚙️ Standing Rulings & Baseline
*   **Base OS:** Arch Linux, built via `archiso`.
*   **Target Experience:** Windows-style installer wizard, gaming-optimized defaults, and Wine/Proton pre-integrated.
*   **Engineering Discipline:** The strict **verify-before-proceed** discipline carries over unchanged from the kernel project. We inspect actual logs, file outputs, and boot menus at every single milestone.

---

## 🗺️ Phases of Development

### 📦 PHASE 0 — Toolchain Setup
*   [x] Install Arch-on-WSL2.
*   [x] Install `archiso` packaging toolchain.
*   [x] Automate the build process using custom monitoring scripts (`run_build.ps1`, `progress.html`).
*   [x] Compile and verify a baseline stock Arch ISO.
*   [x] Verify the live ISO successfully boots in QEMU with WHPX hardware acceleration on Windows.

### 👥 PHASE 1 — Minimal Custom Profile
*   Fork the default `releng` archiso profile configuration into your own custom profile (`arcadeos`).
*   Verify that your own custom profile name/structure compiles and boots successfully with **zero functional changes** first. This proves the customization pipeline itself is working before adding content.

### 🐧 PHASE 2 — Base Package Set & Kernel Choice
*   Select a gaming-oriented performance kernel (e.g., `linux-zen` or `linux-cachyos` for lower latency scheduling).
*   Select the base desktop environment (KDE Plasma is recommended due to robust Wayland support, HDR development, and direct integration with gaming tools).
*   Add the packages and confirm the distro boots successfully to a desktop environment, rather than a minimal command shell.

### 💿 PHASE 3 — Installer
*   Integrate the **Calamares** installer framework (used by user-friendly distros like EndeavourOS and Manjaro to provide a themeable, wizard-driven "Windows-style install" experience).
*   Create a virtual hard disk in QEMU and verify a real, permanent installation to disk works successfully (not just live-booting).

### 🎮 PHASE 4 — Wine / Proton / Compatibility Layer Integration
*   Pre-bundle core translation layers: Wine, Proton-GE, and graphics libraries.
*   Pre-bundle or configure a graphical game manager (such as Steam, Lutris, Heroic Games Launcher, or a custom frontend).
*   Verify that an actual Windows game or executable launches and runs smoothly in the test environment.

### ⚡ PHASE 5 — Gaming Optimizations
*   **GameMode:** Bundle and configure Feral Interactive's GameMode for CPU governor and process priority adjustments while playing.
*   **GPU Drivers:** Pre-configure native drivers (Mesa for AMD/Intel, NVIDIA proprietary drivers).
*   **Kernel Tweaks:** Apply performance scheduler parameters and memory swappiness optimizations (following a measure-before-tuning discipline).
*   **App & Emulator Bundling:** Pre-install popular gaming launchers, web browsers, engines, and emulators:
    *   *Launchers/Browsers:* Steam, Epic Games Launcher, Riot Games Installer, Chrome, Opera GX.
    *   *Game Engines:* Unity, Godot, Unreal Engine.
    *   *Emulators:* Vita3K (PS Vita), Xemu (Xbox), Citra/Azahar (3DS), and other popular emulation systems.
    *   *Optional:* Add an easy dualboot configuration mode (potentially bundled with Batocera).

### 🎨 PHASE 6 — Desktop/Launcher Identity & Theming
*   Apply custom ArcadeOS desktop wallpapers, lock screens, system icons, and boot splash screens (`plymouth`).
*   Implement a dual-mode option: a full desktop environment interface vs. a steam-launcher-first console mode shell (`gamescope` session, similar to SteamOS).

### 🛠️ PHASE 7 — Polish & Distribution
*   Define the official ISO packaging and distribution pipeline.
*   Develop an update/maintenance strategy for system packages.
*   Provide complete documentation and begin physical hardware testing outside of virtual QEMU emulators.

### 🖥️ PHASE 8 — Windows-Style Installer Layout
*   Refine the Calamares installer themes to mimic a highly simplified, welcoming, and user-friendly "Windows-style" wizard interface for maximum accessibility.
