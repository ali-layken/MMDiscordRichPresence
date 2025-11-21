#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"
#include <string.h> 

RECOMP_IMPORT(".", void init_discord_client())
RECOMP_IMPORT(".", void update_discord_client())
RECOMP_IMPORT(".", void update_discord_rich_presence())

RECOMP_HOOK("Player_Init") void read_new_zone_data(Actor* thisx, PlayState* play){
    // TO DO: (Scene Info in Updates)
    //s16 sceneId = play->sceneId;
    //recomp_printf("[discord-rp] Scene changed: id=%d\n", sceneId);
    
    // Update Rich Presence on Player Load
    update_discord_rich_presence();
}

RECOMP_CALLBACK("*", recomp_on_init) void on_recomp_init(){
    // Start Discord Client and Rich Presence
    init_discord_client();
}

RECOMP_CALLBACK("*", recomp_on_play_main) void on_recomp_update(PlayState* play){
    // Keep Discord Client Alive
    update_discord_client();
}

