# PowerShell version update script
param(
    [Parameter(Mandatory=$true)]
    [string]$Version
)

# Validate version format
if ($Version -notmatch '^\d+\.\d+\.\d+$') {
    Write-Error "Version must be in format X.Y.Z (e.g., 2.0.2)"
    exit 1
}

Write-Host "Updating project to version $Version..." -ForegroundColor Green

# Update platformio.ini
$content = Get-Content "platformio.ini" -Raw
$content = $content -replace 'PROJECT_VERSION="[^"]*"', "PROJECT_VERSION=`"v$Version`""
Set-Content "platformio.ini" -Value $content

# Update README.md versions section
$readmeContent = Get-Content "README.md" -Raw
$date = Get-Date -Format "yyyy-MM-dd"
$newVersionsSection = @"
## 📋 Versions

**v$Version** - Latest release ($date)

**v2.0.1** - Minor updates and fixes (2025-12-30)

**v2.0** - Second release (2025-12-30)

**v1.0** - Initial release (2025-12-16)
"@

$readmeContent = $readmeContent -replace '(?s)## 📋 Versions.*?(?=\*\*v[0-9])', $newVersionsSection

# Update startup message reference
$readmeContent = $readmeContent -replace 'M5 Dial Font Display v[\d.]+', "M5 Dial Font Display v$Version"
Set-Content "README.md" -Value $readmeContent

Write-Host "Files updated successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "To complete the version release:" -ForegroundColor Yellow
Write-Host "  1. Review changes: git diff"
Write-Host "  2. Commit changes: git add . && git commit -m 'Release v$Version'"
Write-Host "  3. Create tag: git tag v$Version"
Write-Host "  4. Push: git push origin main --tags"

Write-Host ""
Write-Host "PROJECT_VERSION definitions in platformio.ini:" -ForegroundColor Cyan
Select-String -Path "platformio.ini" -Pattern "PROJECT_VERSION"