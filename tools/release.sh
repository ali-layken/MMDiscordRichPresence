#!/bin/bash
set -e

cd build

cp host/* .
cp ../assets/* .

zip mm_recomp_discord_rich_presence_linux.zip \
    mm_recomp_discord_rich_presence.nrm \
    libdiscord_integration.so \
    libdiscord_partner_sdk.so

zip mm_recomp_discord_rich_presence.zip \
    mm_recomp_discord_rich_presence.zip \
    icon.png \
    manifest.json \
    README.md \
    CHANGELOG.md

echo "✔ Created build/mm_recomp_discord_rich_presence.zip"
