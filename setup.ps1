# Quick Setup Script for LovyanGFX Font Display

Write-Host "🎨 Setting up LovyanGFX Font Display for VSCode + PlatformIO..." -ForegroundColor Cyan

# Check if VSCode is installed
$vscode = Get-Command "code" -ErrorAction SilentlyContinue
if (-not $vscode) {
    Write-Host "❌ VSCode not found. Please install Visual Studio Code first." -ForegroundColor Red
    Write-Host "   Download from: https://code.visualstudio.com/" -ForegroundColor Yellow
    exit 1
}

# Check if PlatformIO CLI is available
$pio = Get-Command "pio" -ErrorAction SilentlyContinue
if (-not $pio) {
    Write-Host "⚠️ PlatformIO CLI not found. Installing via pip..." -ForegroundColor Yellow
    python -m pip install platformio
}

# Open the workspace
Write-Host "📂 Opening VSCode workspace..." -ForegroundColor Green
code "LovyanGFX_M5Dial.code-workspace"

# Install dependencies
Write-Host "📦 Installing PlatformIO dependencies..." -ForegroundColor Green
pio pkg install

Write-Host "✅ Setup complete!" -ForegroundColor Green
Write-Host ""
Write-Host "Next steps:" -ForegroundColor Cyan
Write-Host "1. Install recommended VSCode extensions when prompted" -ForegroundColor White
Write-Host "2. Connect your M5Stack Dial device" -ForegroundColor White  
Write-Host "3. Press Ctrl+Shift+P → 'PlatformIO: Upload' to build and flash" -ForegroundColor White
Write-Host "4. Use serial monitor to see debug output" -ForegroundColor White