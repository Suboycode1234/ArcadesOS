# 📜 ArcadeOS Roadmap v5 — Gaming Linux Distribution

Supersedes the kernel-based roadmap (v0–v4). Previous kernel work archived as a separate completed learning project, not a dependency.

## ⚙️ Standing Rulings
*   **Base:** Arch Linux, built via `archiso`.
*   **Target Experience:** Windows-style installer, gaming-optimized defaults, Wine/Proton pre-integrated.
*   **Methodology:** Verify-before-proceed discipline carries over unchanged from the kernel project.

---

## 🛠️ Phases

### PHASE 0 — Toolchain Setup (✅ COMPLETED)
*   Arch-on-WSL2 configured.
*   `archiso` installed.
*   Stock unmodified ISO builds and boots in QEMU successfully.

### PHASE 1 — Minimal Custom Profile (🔄 NEXT PHASE)
*   Fork the `releng` archiso profile into your own (ArcadeOS profile name).
*   Zero functional changes yet — just confirm your own profile name/structure builds and boots, proving the customization pipeline itself works before adding real content.

### PHASE 2 — Base Package Set & Kernel Choice
*   Select a gaming-oriented kernel (`linux-zen` or `linux-cachyos` — lower latency scheduler, common in gaming distros).
*   Base desktop environment selection (KDE Plasma is the common choice for Nobara/Bazzite-style distros — good Wayland + gaming-tool integration).
*   Confirm boots with real package set, not just stock minimal live environment.

### PHASE 3 — Installer
*   Integrate Calamares (the installer framework most user-friendly Arch/Fedora-based distros use — themeable, supports the "Windows-style install wizard" experience).
*   Confirm a real install-to-disk works in a QEMU virtual disk (not just live-boot).

### PHASE 4 — Wine / Proton / Compatibility Layer Integration
*   Pre-bundle Wine, Proton-GE.
*   Pre-bundle or integrate a launcher (Steam, Lutris, or a custom front-end).
*   Confirm a real existing Windows game/program actually launches and runs.

### PHASE 5 — Gaming Optimizations
*   GameMode (CPU governor/priority tweaks while gaming).
*   GPU driver bundling (NVIDIA/AMD/Mesa as appropriate).
*   Kernel-level tweaks (scheduler, swappiness, etc.) — measure before tuning, same profiling discipline as before.
*   **Additional Steps:** Auto-install and bundle Steam, Epic Games, Riot installer, Chrome, Opera GX, Unreal Engine, Unity, Godot, Vita3k, Xemu, azahar/citra, and most popular emulators. (Optional: Add an easy dualboot mode? with a bundled Batocera?)

### PHASE 6 — Desktop/Launcher Identity & Theming
*   Custom branding, boot splash, theme.
*   Decide: full desktop environment, or a game-launcher-first "console mode" shell (SteamOS-style gamescope session) as an alternative/additional mode.

### PHASE 7 — Polish & Distribution
*   ISO release process, update/maintenance strategy.
*   Documentation, install testing across more hardware than just QEMU.
