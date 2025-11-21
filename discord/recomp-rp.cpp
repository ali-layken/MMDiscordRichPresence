#define DISCORDPP_IMPLEMENTATION
#include "discordpp.h"
#include "modding.h"

#include <memory>
#include <atomic>
#include <cstdio>
#include <thread>

static std::shared_ptr<discordpp::Client> client;
const uint64_t APPLICATION_ID = 1440828904968425563;

static void discord_startup() {
    client = std::make_shared<discordpp::Client>();
    printf("Discord Client Version: %d\n", client->GetVersionMajor());
    client->AddLogCallback([](auto message, auto severity) {
        printf("[discord-rp][discord-client] %s: %s\n", EnumToString(severity), message.c_str());
    }, discordpp::LoggingSeverity::Info);
    client->SetStatusChangedCallback([](discordpp::Client::Status status, discordpp::Client::Error error, int32_t errorDetail) {
        printf("[discord-rp][discord-client]🔄 Status changed: %s\n", discordpp::Client::StatusToString(status).c_str());

        if (status == discordpp::Client::Status::Ready) {
            printf("[discord-rp][discord-client]✅ Client is ready! You can now call SDK functions.\n");
            printf("[discord-rp][discord-client]👥 Friends Count: %zu\n", client->GetRelationships().size());

            discordpp::Activity activity;
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
            
            client->UpdateRichPresence(activity, [](discordpp::ClientResult result) {
            if(result.Successful()) {
                printf("[discord-rp][discord-client]🎮 Rich Presence updated successfully!\n");
            } else {
                printf("[discord-rp][discord-client]❌ Rich Presence update failed\n");
            }
        });

        } else if (error != discordpp::Client::Error::None) {
            printf("[discord-rp][discord-client]❌ Connection Error: %s - Details: %d\n", discordpp::Client::ErrorToString(error).c_str(), errorDetail);
        }
    });

    auto codeVerifier = client->CreateAuthorizationCodeVerifier();
    discordpp::AuthorizationArgs args{};
    args.SetClientId(APPLICATION_ID);
    args.SetScopes(discordpp::Client::GetDefaultPresenceScopes());
    args.SetCodeChallenge(codeVerifier.Challenge());
    client->Authorize(args, [codeVerifier](auto result, auto code, auto redirectUri) {
        if (!result.Successful()) {
            printf("[discord-rp][discord-client]❌ Authentication Error: %s\n", result.Error().c_str());
            return;
        } else {
            printf("[discord-rp][discord-client]✅ Authorization successful! Getting access token...\n");

            client->GetToken(APPLICATION_ID, code, codeVerifier.Verifier(), redirectUri, [](
                discordpp::ClientResult result,
                std::string accessToken,
                std::string refreshToken,
                discordpp::AuthorizationTokenType tokenType,
                int32_t expiresIn,
                std::string scope
            ) {
              printf("[discord-rp][discord-client]🔓 Access token received! Establishing connection...\n");
              client->UpdateToken(discordpp::AuthorizationTokenType::Bearer,  accessToken, [](discordpp::ClientResult result) {
                if(result.Successful()) {
                    printf("[discord-rp][discord-client]🔑 Token updated, connecting to Discord...\n");
                    client->Connect();
                }
              });
        });
      }
    });

}

static void discord_update() {
    if (!client) return;
    discordpp::RunCallbacks();
}

static void discord_rp_update() {
    if (!client) return;

    discordpp::Activity activity;
    activity.SetType(discordpp::ActivityTypes::Playing);
    activity.SetState("In Game");
    activity.SetDetails("Termina");

    
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

