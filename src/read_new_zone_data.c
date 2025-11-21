#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"

RECOMP_IMPORT(".", void init_discord_client())

RECOMP_HOOK("Player_Init") void read_new_zone_data(
     Actor* thisx
    ,PlayState* play) {
   s16 sceneId = play->sceneId;
   recomp_printf("[MM Mod] Scene changed: id=%d\n", sceneId);
 }

RECOMP_CALLBACK("*", recomp_on_init) void on_recomp_init(){
        init_discord_client();
}

