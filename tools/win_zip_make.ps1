$ErrorActionPreference = "Stop"

Set-Location "build"

Copy-Item -Path "host\*" -Destination "." -Recurse -Force
Copy-Item -Path "..\assets\*" -Destination "." -Recurse -Force

$ZipName = "mm_recomp_discord_rich_presence_windows.zip"

$Files = @(
    "mm_recomp_discord_rich_presence.nrm",
    "discord_integration.dll",
    "discord_partner_sdk.dll"
)

Compress-Archive -Path $Files -DestinationPath $ZipName -Force

Write-Host "Done!"
Set-Location ".."
