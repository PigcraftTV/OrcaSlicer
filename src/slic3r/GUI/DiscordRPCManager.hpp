#pragma once
#include <string>
#include <cstdint>

namespace Slic3r::GUI {

class DiscordRPCManager {
public:
    DiscordRPCManager();
    ~DiscordRPCManager();

    void Initialize();
    void Shutdown();
    void UpdatePresence(const std::string& details, const std::string& state = "", const std::string& small_image_key = "", const std::string& small_image_text = "");

private:
    int64_t m_start_time;
};

} // namespace Slic3r::GUI