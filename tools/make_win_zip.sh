#!/bin/bash
set -e

cd build

cp host/* .
cp ../assets/* .

zip mm_recomp_discord_rich_presence_win.zip \
    mm_recomp_discord_rich_presence.nrm \
    discord_integration.dll \
    libdiscord_partner_sdk.so

echo "Done!"
