#!/bin/bash
set -e

cd build

cp host/* .
cp ../assets/* .

zip mm_recomp_discord_rich_presence_linux.zip \
    mm_recomp_discord_rich_presence.nrm \
    libdiscord_integration.so \
    libdiscord_partner_sdk.so

echo "Done!"
