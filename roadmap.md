# 📜 ArcadeOS Roadmap v5 — Gaming Linux Distribution

Supersedes the kernel-based roadmap (v0–v4). Previous kernel work archived as a separate completed learning project, not a dependency.

---

## ⚖️ Standing Rulings
*   **Base:** Arch Linux, built via `archiso`.
*   **Target Experience:** Windows-style installer, gaming-optimized defaults, Wine/Proton pre-integrated.
*   **Verification:** The strict "verify-before-proceed" discipline carries over unchanged from the kernel project.

---

## 🗺️ Phases

### 🔄 PHASE 0 — Toolchain Setup (Completed & Verified)
*   [x] Set up Arch-on-WSL2.
*   [x] Install `archiso` and build tools.
*   [x] Build a stock, unmodified ISO.
*   [x] Successfully boot and verify the ISO in QEMU with WHPX acceleration.

### 🧩 PHASE 1 — Minimal Custom Profile (Next Step)
*   [ ] Fork the `releng` archiso profile into a custom profile named **ArcadeOS**.
*   [ ] Verify the new profile builds and boots successfully with zero functional changes. This proves the custom profile structure works before adding new features.

### 🐧 PHASE 2 — Base Package Set & Kernel Choice
*   [ ] Select a gaming-oriented kernel (such as `linux-zen` or `linux-cachyos` for lower latency schedulers).
*   [ ] Select the base Desktop Environment (e.g., KDE Plasma for Wayland stability and Nobara/Bazzite-style tool integration).
*   [ ] Confirm system boots successfully with the core packages, not just the minimal live environment.

### 💾 PHASE 3 — Installer Integration
*   [ ] Integrate the **Calamares** installer framework for a user-friendly, Windows-style install wizard.
*   [ ] Verify installation to virtual disk within QEMU (installing to disk, not just live booting).

### 🍷 PHASE 4 — Wine / Proton / Compatibility Layer
*   [ ] Pre-bundle Wine and Proton-GE compatibility layers.
*   [ ] Integrate/pre-bundle a gaming client/manager (Steam, Lutris, or a custom front-end).
*   [ ] Verify launching and running a real Windows game or application.

### ⚡ PHASE 5 — Gaming Optimizations
*   [ ] Integrate **GameMode** (CPU governor and priority scheduling tweaks).
*   [ ] Pre-bundle GPU drivers (AMD/Mesa, Intel, NVIDIA).
*   [ ] Tune kernel parameters (scheduler, swappiness) using a profiling-led approach.
*   [ ] **Software Bundling:** Auto-install and bundle:
    *   *Apps/Browsers:* Steam, Google Chrome, Opera GX.
    *   *Engines:* Unreal Engine, Unity, Godot.
    *   *Emulators:* Vita3K, Xemu, Azahar/Citra, and other popular emulators.
    *   *(Optional):* Integrate dual-boot options / bundle Batocera.

### 🎨 PHASE 6 — Desktop/Launcher Identity & Theming
*   [ ] Implement custom OS branding, boot splash screens, and desktop themes.
*   [ ] Decide on interface behavior: boot directly into a gamepad-friendly "Console Mode" shell (SteamOS-style gamescope session) or load a full desktop environment.

### 📦 PHASE 7 — Polish & Distribution
*   [ ] Establish build release pipeline and update/maintenance strategies.
*   [ ] Create documentation and verify install stability on physical hardware.
