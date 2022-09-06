#include "ui.hh"
#include "../globals.hh"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

void design() {

    ImGuiStyle& style = ImGui::GetStyle();

    style.ScrollbarRounding = 0;
    style.ChildRounding = 0;
    style.FrameRounding = 0;



}


struct tabs_data {
    const char* name;

};

static std::vector<tabs_data> tabs = {
    {"Aimbot"},
    {"Visuals"},
    {"Misc"},

};

static int tab = 0;

void ui::render() {
    if (!globals.active) return;
    design();

    ImGui::SetNextWindowPos(ImVec2(window_pos.x, window_pos.y), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_size.x, window_size.y));
    ImGui::SetNextWindowBgAlpha(1.0f);

    ImGui::Begin(window_title, &globals.active, window_flags);
    {
        if (ImGui::BeginChild("##LeftSide", ImVec2(190, ImGui::GetContentRegionAvail().y), true)) {
            for (unsigned int i = 0; i < tabs.size(); i++) {
                bool selected = (tab == i);

                if (ImGui::Selectable(tabs[i].name, &selected))
                    tab = i;

                if (selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndChild();
        }

        {
            ImGui::SameLine(0);
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();
        }

        if (ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true)) {
            //Centered Text
            auto& data = tabs[tab];
            auto center = [](float avail_width, float element_width, float padding = 0)
            {
                ImGui::SameLine((avail_width / 2) - (element_width / 2) + padding);
            };

            auto center_text = [&](const char* format, float spacing = 15, ImColor color = ImColor(255, 255, 255)) {
                center(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(format).x);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing);
                ImGui::TextColored(color.Value, format);
            };

            //Tabs
            center_text(data.name);
            if (data.name == "Aimbot") {
                if (ImGui::BeginChild("##Main Aimbot", ImVec2(305, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Aimbot Main");
                    ImGui::Text("Text Moment");
                    

                    ImGui::EndChild();
                }
                ImGui::SameLine(0);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                ImGui::SameLine();
                if (ImGui::BeginChild("##Extras Aimbot", ImVec2(240, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Aimbot Extras");
                    ImGui::Text("Text Moment Extra");

                    ImGui::EndChild();
                }
            }

            if (data.name == "Visuals") {
                if (ImGui::BeginChild("##Main Visuals", ImVec2(305, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Visuals Main");
                    ImGui::Button("Click me ");

                    ImGui::EndChild();
                }
                ImGui::SameLine(0);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                ImGui::SameLine();
                if (ImGui::BeginChild("##Extras Visuals", ImVec2(240, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Visuals Extras");
                    ImGui::Button("Click me Extra");

                    ImGui::EndChild();
                }
            }

            if (data.name == "Misc") {
                if (ImGui::BeginChild("##Main Misc", ImVec2(305, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Misc Main");
                    ImGui::Checkbox("Check me", &globals.checkme);

                    ImGui::EndChild();
                }
                ImGui::SameLine(0);
                ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
                ImGui::SameLine();
                if (ImGui::BeginChild("##Extras Misc", ImVec2(240, ImGui::GetContentRegionAvail().y), true)) {
                    center_text("Misc Extras");
                    ImGui::Checkbox("Check me Extra", &globals.checkmeextra);

                    ImGui::EndChild();
                }
            }

            ImGui::EndChild();
        }

    }  
    ImGui::End();
}

void ui::init(LPDIRECT3DDEVICE9 device) {
    dev = device;
	
    // colors
    ImGui::StyleColorsDark();

	if (window_pos.x == 0) {
		RECT screen_rect{};
		GetWindowRect(GetDesktopWindow(), &screen_rect);
		screen_res = ImVec2(float(screen_rect.right), float(screen_rect.bottom));
		window_pos = (screen_res - window_size) * 0.5f;

		// init images here
	}
}