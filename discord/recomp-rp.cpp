#define DISCORDPP_IMPLEMENTATION
#include "discordpp.h"
#include "modding.h"

#include <memory>
#include <atomic>
#include <cstdio>

static std::shared_ptr<discordpp::Client> client;
static std::atomic<bool> running = true;
const uint64_t APPLICATION_ID = 1440828904968425563;

static void discordStartup() {
    printf("[MM Mod] discordStartup: before make_shared\n");

    try {
        client = std::make_shared<discordpp::Client>();
        printf("[MM Mod] discordStartup: after make_shared (OK), client %s\n",
               client ? "non-null" : "NULL");
    } catch (const std::exception& e) {
        printf("[MM Mod] discordStartup: exception: %s\n", e.what());
    } catch (...) {
        printf("[MM Mod] discordStartup: unknown exception\n");
    }
}


extern "C" { 
    RECOMP_EXPORT_DATA uint32_t recomp_api_version = 1;

    RECOMP_EXPORT_FUNC void init_discord_client() {
        printf("[MM Mod] init_discord_client: entered\n");

        discordStartup();

        printf("[MM Mod] init_discord_client: finished discordStartup\n");
    }
}
