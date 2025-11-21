# Majora's Mask: Discord Rich Presence

## Install
Use the ingame install mods button and give it the .zip downloaded from _Releases_ it should put 2 files in the mod folder and the .nrm.

## TO DO:
1. atm, rich presence is updated on `Player_Init` meaning I have access to the current scene -> could be displayed in discord.
however theres no scene to name map yet, maybe when translations are implmented? I could just extract all the info from the scene table file I saw somwhere.

1. it would be really cool to allow mod code to run before the game is selected especially for cross-game mods like this one. If i could start my mod code on the launcher instead of on `recomp_on_init` then I could truly display "In Menus" when in menus, and "Hyrule - Scene Name" when in game in OOT.