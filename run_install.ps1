$progressFile = "C:\Users\sethj\ArcadeOS\install_progress.txt"

# Reset progress
"0|[░░░░░░░░░░░░░░░░░░░░]|Initializing..." | Out-File -FilePath $progressFile -Encoding utf8 -Force

# Start pacman install in the background
$wslProcess = Start-Process wsl.exe -ArgumentList "-d archlinux sh -c ""pacman -Syu --noconfirm && pacman -S --noconfirm archiso git base-devel && pacman -Scc --noconfirm""" -RedirectStandardOutput "C:\Users\sethj\ArcadeOS\install.log" -RedirectStandardError "C:\Users\sethj\ArcadeOS\install_err.log" -PassThru -NoNewWindow

while (-not $wslProcess.HasExited) {
    Start-Sleep -Seconds 2
    if (Test-Path "C:\Users\sethj\ArcadeOS\install.log") {
        $log = Get-Content "C:\Users\sethj\ArcadeOS\install.log" -ErrorAction SilentlyContinue
        if ($log) {
            # Count upgrading and installing actions
            $upgrades = ($log | Select-String "upgrading ").Count
            $installs = ($log | Select-String "installing ").Count
            
            $totalActions = 75 # Approximate total packages (26 upgrades + 49 installs)
            $completed = $upgrades + $installs
            
            $pct = [math]::Min(95, [math]::Round(($completed / $totalActions) * 100))
            if ($log -match "Running post-transaction hooks") {
                $pct = [math]::Max($pct, 90)
            }
            
            $barLength = [math]::Round($pct / 5)
            $bar = ("█" * $barLength) + ("░" * (20 - $barLength))
            
            $status = "Installing packages..."
            if ($log -match "Retrieving packages") { $status = "Downloading packages..." }
            if ($log -match "Rebuilding certificate stores") { $status = "Finishing installation..." }
            
            "$pct|[$bar]|$status" | Out-File -FilePath $progressFile -Encoding utf8 -Force
        }
    }
}

if ($wslProcess.ExitCode -eq 0) {
    "100|[████████████████████]|Completed Successfully!" | Out-File -FilePath $progressFile -Encoding utf8 -Force
} else {
    "0|[░░░░░░░░░░░░░░░░░░░░]|Failed with exit code $($wslProcess.ExitCode)" | Out-File -FilePath $progressFile -Encoding utf8 -Force
}
