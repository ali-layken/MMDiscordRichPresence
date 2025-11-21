#define DISCORDPP_IMPLEMENTATION
#include "discordpp.h"
#include "modding.h"

#include <memory>
#include <atomic>
#include <cstdio>
#include <thread>

static std::shared_ptr<discordpp::Client> client;
const uint64_t APPLICATION_ID = 1440828904968425563;

// Discord SDK Setup (copied from their guides mostly)
static void discord_startup() {
    client = std::make_shared<discordpp::Client>();
    client->SetApplicationId(APPLICATION_ID);

    discordpp::Activity activity;
    activity.SetName("Zelda64Recomp");
    activity.SetType(discordpp::ActivityTypes::Playing);
    activity.SetState("In Menus");
    activity.SetDetails("Termina");

    discordpp::ActivityTimestamps timestamps;
    timestamps.SetStart(time(nullptr));
    activity.SetTimestamps(timestamps);

    discordpp::ActivityAssets assets;
    assets.SetLargeImage("output");
    assets.SetLargeText("File Select");
    activity.SetAssets(assets);
    
    client->UpdateRichPresence(activity, [](const discordpp::ClientResult &result) {
        if(result.Successful()) {
            printf("[discord-rp][discord-client]🎮 Rich Presence updated successfully!\n");
        } else {
            printf(
                "[discord-rp][discord-client]❌ Rich Presence update failed: %s\n",
                result.Error().c_str()
            );
        }
    });
}

// Keeps Discord Client Alive
static void discord_update() {
    if (!client) return;
    discordpp::RunCallbacks();
}

// Updates Rich Presence On Game Update
static void discord_rp_update() {
    if (!client) return;

    discordpp::Activity activity;
    activity.SetType(discordpp::ActivityTypes::Playing);
    activity.SetName("Zelda64Recomp");
    activity.SetState("In Game");
    activity.SetDetails("Termina");

    discordpp::ActivityAssets assets;
    assets.SetLargeImage("output");
    assets.SetLargeText("File Select");
    activity.SetAssets(assets);

    
    client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
        if(result.Successful()) {
            printf("[discord-rp][discord-client]🎮 Rich Presence updated successfully!\n");
        } else {
            printf("[discord-rp][discord-client]❌ Rich Presence update failed\n");
        }
    });
}


extern "C" { 
    RECOMP_EXPORT_DATA uint32_t recomp_api_version = 1;

    RECOMP_EXPORT_FUNC void init_discord_client() {
        discord_startup();
    }

    RECOMP_EXPORT_FUNC void update_discord_client() {
        discord_update();
    }

    RECOMP_EXPORT_FUNC void update_discord_rich_presence(){
        discord_rp_update();
    }

}

