#!/bin/bash
set -e

cd build

cp host/* .
cp ../assets/* .

zip mm_recomp_discord_rich_presence_mac.zip \
    mm_recomp_discord_rich_presence.nrm \
    libdiscord_integration.dylib \
    libdiscord_partner_sdk.dylib

echo "Done!"
