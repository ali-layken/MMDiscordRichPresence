$ErrorActionPreference = "Stop"

$LLVM21 = "C:\Program Files\LLVM\LLVM 21\bin"
$LLVM18 = "C:\Program Files\LLVM\LLVM 18\bin"

$env:HOST_CXX = "$LLVM21\clang++.exe"
$env:CC       = "$LLVM18\clang.exe"
$env:LD       = "$LLVM18\ld.lld.exe"

make clean

make -j16

./RecompModTool.exe mod.toml ./build

Write-Host "✅ Done!"