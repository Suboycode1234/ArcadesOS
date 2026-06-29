# install_wsl2.ps1 - Automated WSL2 & Arch Linux setup helper for ArcadeOS
# Run this from an Administrator PowerShell prompt!

Write-Host "=============================================" -ForegroundColor Cyan
Write-Host "   WSL2 & Arch Linux Installer Helper       " -ForegroundColor Cyan
Write-Host "=============================================" -ForegroundColor Cyan

# 1. Check for Administrator Privileges
$isAdmin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
if (-not $isAdmin) {
    Write-Host "[!] ERROR: This script must be run as Administrator." -ForegroundColor Red
    Write-Host "Please close this terminal, right-click PowerShell, select 'Run as Administrator', and run this script again." -ForegroundColor Yellow
    Exit 1
}

# 2. Check if WSL is already installed
$wslInstalled = $false
try {
    $null = wsl --status -ErrorAction SilentlyContinue
    $wslInstalled = $true
    Write-Host "[+] WSL is already installed on this machine." -ForegroundColor Green
} catch {
    Write-Host "[-] WSL is not detected. Proceeding with installation..." -ForegroundColor Yellow
}

if (-not $wslInstalled) {
    Write-Host "[*] Enabling Windows Subsystem for Linux..." -ForegroundColor Cyan
    dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart | Out-Null

    Write-Host "[*] Enabling Virtual Machine Platform..." -ForegroundColor Cyan
    dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart | Out-Null

    Write-Host "[*] Installing WSL package..." -ForegroundColor Cyan
    wsl --install --no-distribution

    Write-Host "[!] IMPORTANT: A system restart is required to finish WSL installation." -ForegroundColor Yellow
    Write-Host "Please restart your computer, then run this script again to set up the Arch Linux environment." -ForegroundColor Green
    Exit 0
}

# 3. Configure WSL default version to 2
Write-Host "[*] Setting WSL default version to 2..." -ForegroundColor Cyan
wsl --set-default-version 2

# 4. Check if Arch Linux is installed in WSL
$distros = wsl -l -v 2>$null
$archInstalled = $false
if ($distros) {
    if ($distros -match "archlinux") {
        $archInstalled = $true
        Write-Host "[+] Arch Linux is already registered in WSL2." -ForegroundColor Green
    }
}

if (-not $archInstalled) {
    Write-Host "[*] Arch Linux distribution not found." -ForegroundColor Yellow
    Write-Host "[*] To install Arch Linux on WSL2, you have a few options:" -ForegroundColor Cyan
    Write-Host "    Option A: Run 'wsl --install -d archlinux' if available on your Windows Store index." -ForegroundColor White
    Write-Host "    Option B: Download the official .AppxBundle from Microsoft Store/GitHub and install it." -ForegroundColor White
    Write-Host ""
    
    $installChoice = Read-Host "Would you like me to try installing Arch Linux via wsl --install now? (y/n)"
    if ($installChoice -eq 'y' -or $installChoice -eq 'Y') {
        Write-Host "[*] Triggering: wsl --install -d archlinux" -ForegroundColor Cyan
        wsl --install -d archlinux
        
        Write-Host "[+] Installation command completed. Please verify it registered by running: wsl -l -v" -ForegroundColor Green
    } else {
        Write-Host "[*] Skipping automatic installation. Please install Arch Linux manually before running the ArcadeOS build script." -ForegroundColor Yellow
    }
} else {
    Write-Host "[+] WSL2 & Arch Linux environment setup is ready for the ArcadeOS toolchain." -ForegroundColor Green
    Write-Host "[*] You can now proceed to run: .\run_install.ps1 (to install the build package dependencies)." -ForegroundColor Cyan
}

Write-Host "=============================================" -ForegroundColor Cyan
Write-Host "   Setup Verification Complete!             " -ForegroundColor Cyan
Write-Host "=============================================" -ForegroundColor Cyan
