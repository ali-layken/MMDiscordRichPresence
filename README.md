# Majora's Mask: Discord Rich Presence

Download the mod `.zip` from [Thunderstore](https://thunderstore.io/c/zelda-64-recompiled/p/BeanProductions/Discord_Rich_Presence/) or [Releases](https://github.com/ali-layken/MMDiscordRichPresence/releases)

## Install
Use the ingame `Install Mods` button in the Mod Menu, and give it the downloaded `.zip` it should put 2 files in the mod folder and the `.nrm`.

## Samples
<img width="2202" height="1064" alt="image" src="https://github.com/user-attachments/assets/1da7fa85-40a2-419c-9272-acd8b742f42f" />

## TO DO:
1. Rich presence is updated on `Player_Init` meaning I have access to the current scene -> could be displayed in discord.
however theres no scene to name map yet, maybe when translations are implmented? I could just extract all the info from the scene table file I saw somwhere.

1. It would be really cool to allow mod code to run before the game is selected especially for cross-game mods like this one. If i could start my mod code on the launcher instead of on `recomp_on_init` then I could truly display "In Menus" when in menus, and "Hyrule - Scene Name" when in game in OOT.

1. On click activity open Zelda64Recomp info page

I am thinking I will release v2 with oot support when that comes out, and in that update i'll work on writing the current area to rich presence
