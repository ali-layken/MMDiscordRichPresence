#include "modding.h"
#include "global.h"
#include "recomputils.h"
#include "recompconfig.h"


RECOMP_HOOK("Player_Init") void read_new_zone_data(
     Actor* thisx
    ,PlayState* play) {
   s16 sceneId = play->sceneId;
   recomp_printf("[MM Mod] Scene changed: id=%d\n", sceneId);
 }


