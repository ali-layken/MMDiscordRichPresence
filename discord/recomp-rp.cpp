#define DISCORDPP_IMPLEMENTATION
#include "discordpp.h"
#include "modding.h"

#include <memory>
#include <atomic>
#include <cstdio>
#include <ctime> 
#include <thread>

class DiscordIntegration{
    public:
        DiscordIntegration(){
            printf("in construuctor!");
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

        ~DiscordIntegration() {
            printf("we deconstructing plz right??");
        }

        void UpdateClient() {
            if (client)
                discordpp::RunCallbacks();
        }

        void UpdateRP(){
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

    private:
        static constexpr uint64_t APPLICATION_ID = 1440828904968425563;
        std::shared_ptr<discordpp::Client> client;
};

static DiscordIntegration* g_discord = nullptr;

RECOMP_EXPORT_DATA uint32_t recomp_api_version = 1;

RECOMP_EXPORT_FUNC void init_discord_client() {
    printf("in init recomp");
    if (!g_discord) g_discord = new DiscordIntegration();
}

RECOMP_EXPORT_FUNC void update_discord_client() {
    if (g_discord) g_discord->UpdateClient();
}

RECOMP_EXPORT_FUNC void update_discord_rich_presence(){
    if (g_discord) g_discord->UpdateRP();
}


