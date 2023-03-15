
if (-not Get-Command xmake) {
    
    if (Get-Command scoop) {
        Write-Host "Installing Xmake via Scoop package manager." -ForegroundColor Cyan
        scoop install xmake
    }
    else {
        Write-Host "Installing Xmake via Winget package manager." -ForegroundColor Cyan
        winget install xmake
    }

}
