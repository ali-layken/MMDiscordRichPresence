#!/bin/bash
set -e

cd build

cp host/* .
cp ../assets/* .


zip mm_recomp_discord_rich_presence.zip mod.json mod_binary.bin mod_syms.bin thumb.png
mv mm_recomp_discord_rich_presence.zip mm_recomp_discord_rich_presence.nrm
zip mm_recomp_discord_rich_presence.zip mm_recomp_discord_rich_presence.nrm  libdiscord_integration.so libdiscord_integration.dylib libdiscord_integration.dll libdiscord_partner_sdk.so libdiscord_partner_sdk.dylib discord_partner_sdk.dll 

echo "✔ Created build/mm_recomp_discord_rich_presence.zip"