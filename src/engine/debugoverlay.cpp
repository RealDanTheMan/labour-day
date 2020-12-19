#include "debugoverlay.hpp"
#include "imguiinterface.hpp"

using namespace Engine;


DebugOverlay::DebugOverlay(EngineCore * const engine):
m_core(engine)
{

}

void DebugOverlay::OnUpdate()
{
    DrawPerfStats();
}

void DebugOverlay::DrawPerfStats() const
{
    std::string fps = "";
    std::string frameTime = "";

    assert (m_core != nullptr);
    fps = std::to_string(m_core->FPS()->Get());
    frameTime = std::to_string(m_core->FPS()->GetMilliseconds());

    //ImGui::NewFrame();
    ImGui::Begin("Perf Stats Panel");
    ImGui::AlignTextToFramePadding();
    ImGui::Text("FPS: ", nullptr); ImGui::SameLine();
    ImGui::Text(fps.c_str(), nullptr);

    ImGui::Text("Frame Time: ", nullptr); ImGui::SameLine();
    ImGui::Text(frameTime.c_str(), nullptr);
    ImGui::End();
    //ImGui::Render();
}