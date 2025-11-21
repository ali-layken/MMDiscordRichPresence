#include "discordpp.h"
#include "modding.h"
#include "recomputils.h"

#include <csignal>
#include <thread>

static std::shared_ptr<discordpp::Client> client;
const uint64_t APPLICATION_ID = 1440828904968425563;
static std::atomic<bool> running = true;
void signalHandler(int signum) {
        running.store(false);
}

extern "C" {
    RECOMP_EXPORT_DATA uint32_t recomp_api_version = 1;

    RECOMP_CALLBACK("*", recomp_on_init) void start_discord_rp(){
        recomp_printf("Starting Discord Rich Presence...\n");
        
        signal(SIGINT, signalHandler);
        client = std::make_shared<discordpp::Client>();
        client->AddLogCallback([](auto message, auto severity) {
            recomp_printf("[Discord SDK] %s\n", message.c_str());
        }, discordpp::LoggingSeverity::Info);

        client->SetStatusChangedCallback([](discordpp::Client::Status status, discordpp::Client::Error error, int32_t detail) {
            recomp_printf("[Discord SDK] Status: %s\n", discordpp::Client::StatusToString(status).c_str());

            if (status == discordpp::Client::Status::Ready) {
                recomp_printf("[Discord SDK] Ready.\n");
            }
        });

        client->Connect();

        std::thread([] {
            while (running.load()) {
                discordpp::RunCallbacks();
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
            if (client) {
            recomp_printf("Disconnecting Discord...\n");
            client->Disconnect();
        }
        }).detach();
    }
}
