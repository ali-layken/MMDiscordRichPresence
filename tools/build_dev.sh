#!/bin/bash

echo "🧹 Cleaning build..."
make clean

echo "🔨 Building mod with 16 threads..."
make -j$(nproc)

echo "📦 Packaging mod..."
./RecompModTool mod.toml ./build

echo "📂 Copying mod files to Recompiled mods folder..."
cp ./build/mm_recomp_discord_rich_presence.nrm ~/.config/Zelda64Recompiled/mods/mm_recomp_discord_rich_presence.nrm
cp ./build/host/libdiscord_integration.so ~/.config/Zelda64Recompiled/mods/libdiscord_integration.so
cp ./build/host/libdiscord_partner_sdk.so ~/.config/Zelda64Recompiled/mods/libdiscord_partner_sdk.so

echo "✅ Done!"
