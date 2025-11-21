#!/bin/bash

echo "🧹 Cleaning build..."
make clean

echo "🔨 Building mod with 16 threads..."
make -j$(nproc)

echo "📦 Packaging mod..."
./RecompModTool mod.toml ./build

echo "✅ Done!"