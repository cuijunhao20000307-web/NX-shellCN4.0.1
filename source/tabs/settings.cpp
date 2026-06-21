#define IMGUI_DEFINE_MATH_OPERATORS

#include "config.hpp"
#include "fs.hpp"
#include "gui.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "language.hpp"
#include "net.hpp"
#include "popups.hpp"
#include "tabs.hpp"
#include "usb.hpp"

namespace Tabs {
    static bool update_popup = false, network_status = false, update_available = false, unmount_popup = false;
    static std::string tag_name = std::string();

    static void Indent(const std::string &title) {
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::TextColored(ImGui::GetStyle().Colors[ImGuiCol_CheckMark], title.c_str());
        ImGui::Indent(20.f);
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
    }

    static void Separator(void) {
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Unindent();
        ImGui::Separator();
    }

    void Settings(WindowData &data) {
        if (ImGui::BeginTabItem("设置")) {
            ImGui::Indent(10.f);
            Tabs::Indent(strings[cfg.lang][Lang::SettingsUSBTitle]);

            if (!USB::Connected()) {
                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
            }

            if (ImGui::Button(strings[cfg.lang][Lang::SettingsUSBUnmount], ImVec2(250, 50)))
                unmount_popup = true;

            if (!USB::Connected()) {
                ImGui::PopItemFlag();
                ImGui::PopStyleVar();
            }

            Tabs::Separator();
            Tabs::Indent(strings[cfg.lang][Lang::SettingsImageViewTitle]);
            if (ImGui::Checkbox(strings[cfg.lang][Lang::SettingsImageViewFilenameToggle], std::addressof(cfg.image_filename)))
                Config::Save(cfg);

            Tabs::Separator();
            Tabs::Indent(strings[cfg.lang][Lang::SettingsDevOptsTitle]);
            if (ImGui::Checkbox(strings[cfg.lang][Lang::SettingsDevOptsLogsToggle], std::addressof(cfg.dev_options)))
                Config::Save(cfg);

            Tabs::Separator();
            Tabs::Indent(strings[cfg.lang][Lang::SettingsMultiLangTitle]);
            if (ImGui::Checkbox(strings[cfg.lang][Lang::SettingsMultiLangLogsToggle], std::addressof(cfg.multi_lang)))
                Config::Save(cfg);

            Tabs::Separator();
            Tabs::Indent(strings[cfg.lang][Lang::SettingsAboutTitle]);
            ImGui::Text("NX-Shell %s: v%d.%d.%d", strings[cfg.lang][Lang::SettingsAboutVersion], VERSION_MAJOR, VERSION_MINOR, VERSION_MICRO);
            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Text("Dear ImGui %s: %s", strings[cfg.lang][Lang::SettingsAboutVersion], ImGui::GetVersion());
            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Text("%s: Joel16", strings[cfg.lang][Lang::SettingsAboutAuthor]);
            ImGui::Dummy(ImVec2(0.0f, 5.0f));
            ImGui::Text("%s: Preetisketch", strings[cfg.lang][Lang::SettingsAboutBanner]);
            ImGui::Dummy(ImVec2(0.0f, 5.0f));

            if (ImGui::Button(strings[cfg.lang][Lang::SettingsCheckForUpdates], ImVec2(250, 50))) {
                tag_name = Net::GetLatestReleaseJSON();
                network_status = Net::GetNetworkStatus();
                update_available = Net::GetAvailableUpdate(tag_name);
                update_popup = true;
            }

            ImGui::EndTabItem();
        }

        if (update_popup)
            Popups::UpdatePopup(update_popup, network_status, update_available, tag_name);
        if (unmount_popup)
            Popups::USBPopup(unmount_popup);
    }
}
