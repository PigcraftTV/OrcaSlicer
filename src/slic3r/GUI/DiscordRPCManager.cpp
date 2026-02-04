#include "DiscordRPCManager.hpp"
#include "libslic3r/Utils.hpp" // For get_current_pid
#include <discord_rpc.h>
#include <chrono>
#include <cstring> // For memset

namespace Slic3r::GUI {

static const char* APPLICATION_ID = "1468641892622401610";

void DiscordRPCManager::Initialize()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    
    Discord_Initialize(APPLICATION_ID, &handlers, 1, nullptr);

    m_start_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    UpdatePresence("Idle", "Configuring settings");
}

void DiscordRPCManager::Shutdown()
{
    Discord_Shutdown();
}

void DiscordRPCManager::UpdatePresence(const std::string& details, const std::string& state, const std::string& small_image_key, const std::string& small_image_text)
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = state.c_str();
    discordPresence.details = details.c_str();
    discordPresence.startTimestamp = m_start_time;
    discordPresence.largeImageKey = "logo";
    discordPresence.largeImageText = "OrcaSlicer";
    if (!small_image_key.empty()) {
        discordPresence.smallImageKey = small_image_key.c_str();
        discordPresence.smallImageText = small_image_text.c_str();
    }
    
    Discord_UpdatePresence(&discordPresence);
}

DiscordRPCManager::DiscordRPCManager() : m_start_time(0) {}
DiscordRPCManager::~DiscordRPCManager() {}

} // namespace Slic3r::GUI