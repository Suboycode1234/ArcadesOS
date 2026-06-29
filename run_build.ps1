$progressFile = "C:\Users\sethj\ArcadeOS\build_progress.txt"
$logFile      = "C:\Users\sethj\ArcadeOS\build_iso.log"
$errFile      = "C:\Users\sethj\ArcadeOS\build_iso_err.log"
$outputDir    = "C:\Users\sethj\ArcadeOS-distro"

New-Item -ItemType Directory -Force -Path $outputDir | Out-Null

function Write-Progress-File($pct, $status) {
    $filled = [math]::Round($pct / 5)
    $empty  = 20 - $filled
    $bar    = ("#" * $filled) + ("-" * $empty)
    "$pct|[$bar]|$status" | Out-File -FilePath $progressFile -Encoding utf8 -Force
}

Write-Progress-File 0 "Initializing build..."

$buildCmd = "cd ~/archlive && mkarchiso -v -o /tmp/out ."
$wslProcess = Start-Process wsl.exe `
    -ArgumentList "-d archlinux sh -c `"$buildCmd`"" `
    -RedirectStandardOutput $logFile `
    -RedirectStandardError  $errFile `
    -PassThru -NoNewWindow

while (-not $wslProcess.HasExited) {
    Start-Sleep -Seconds 2
    if (Test-Path $logFile) {
        $log = Get-Content $logFile -ErrorAction SilentlyContinue
        if ($log) {
            $pct    = 0
            $status = "Starting build..."

            $installs = ($log | Select-String "installing ").Count
            if ($installs -gt 0) {
                $pct    = [math]::Min(50, [math]::Round(($installs / 451) * 50))
                $status = "Installing packages ($installs/451)..."
            }

            if ($log -match "Updating linux initcpios") {
                $pct    = 55
                $status = "Generating initramfs images..."
            }

            if ($log -match "Setting up SYSLINUX") {
                $pct    = 63
                $status = "Setting up BIOS bootloader (SYSLINUX)..."
            }

            if ($log -match "Setting up systemd-boot") {
                $pct    = 70
                $status = "Setting up UEFI bootloader (systemd-boot)..."
            }

            $squashLines = $log | Select-String -Pattern "\d+%"
            if ($squashLines) {
                $lastLine = $squashLines[-1].Line
                if ($lastLine -match "(\d+)%") {
                    $squashPct = [int]$Matches[1]
                    $pct       = 70 + [math]::Round(($squashPct / 100) * 22)
                    $status    = "SquashFS compression: $squashPct%..."
                }
            }

            if ($log -match "Creating checksum") {
                $pct    = 94
                $status = "Creating checksum file..."
            }

            if ($log -match "Creating ISO image") {
                $pct    = 96
                $status = "Packaging ISO image..."
            }

            Write-Progress-File $pct $status
        }
    }
}

Write-Host "Build exited with code: $($wslProcess.ExitCode)"

$isoPath = wsl -d archlinux -- bash -c "ls /tmp/out/*.iso 2>/dev/null | head -1"
$isoPath = $isoPath.Trim()

if ($isoPath -ne "") {
    $isoName  = ($isoPath -split "/")[-1]
    $destPath = Join-Path $outputDir $isoName
    Write-Progress-File 98 "Copying ISO to Windows..."
    Write-Host "Copying $isoPath => $destPath"
    wsl -d archlinux -- bash -c "cp '$isoPath' '/mnt/c/Users/sethj/ArcadeOS-distro/$isoName'"
    wsl -d archlinux -- bash -c "rm -rf /tmp/out /root/archlive/work"
    Write-Host "Done! ISO at: $destPath"
    Write-Progress-File 100 "Complete! ISO ready: $isoName"
} else {
    Write-Host "ERROR: No ISO found in /tmp/out"
    $ec = $wslProcess.ExitCode
    Write-Progress-File 0 "Build failed (exit $ec) - check build_iso_err.log"
}
