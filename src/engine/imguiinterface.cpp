#include "imguiinterface.hpp"

using namespace Engine;

void IMGuiInterface::Init(Window * win)
{
    assert (win != nullptr);

    IMGUI_CHECKVERSION();
    m_ctx = ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(win->GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void IMGuiInterface::Free()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_ctx = nullptr;
}

void IMGuiInterface::Update()
{
    bool yes = true;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //ImGui::ShowDemoWindow(&yes);

    // Draw panels
    for(IMGuiPanel * const panel : m_panels)
    {
        panel->OnUpdate();
    }

    ImGui::Render();
}

void IMGuiInterface::Render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void IMGuiInterface::AddPanel(IMGuiPanel * const panel)
{
    m_panels.push_back(panel);
    m_panels.back()->OnInit();
}