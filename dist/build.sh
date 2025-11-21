#!/bin/bash

set -e

echo "🧹 Cleaning build..."
make clean

echo "🔨 Building mod with 16 threads..."
make -j16

echo "📦 Packaging mod..."
RecompModTool mod.toml ./build/

echo "📂 Copying mod files to Recompiled mods folder..."
cp ./build/mm_recomp_discord_rich_presence.nrm ~/.config/Zelda64Recompiled/mods/mm_recomp_discord_rich_presence.nrm
cp ./build/host/libdiscord_integration.so ~/.config/Zelda64Recompiled/mods/libdiscord_integration.so

echo "✅ Done!"
