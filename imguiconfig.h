#include "headers el pepe/allincludes.h"
using namespace pointers;

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

//ints ------------------------------------------------------------------------------------------------
static int playerspeed = 1;
static float jumpPower = 2;

//BOOLS ------------------------------------------------------------------------------------------------
bool menuVisible = true;
//bool speedhackIni = false;
bool jumppowerini = false;
//BOOLS END------------------------------------------------------------------------------------------------

int createwindowandconfigimgui() {
  //window---------------------------------------------------------------------------------
  //window---------------------------------------------------------------------------------
  //window---------------------------------------------------------------------------------
  //window---------------------------------------------------------------------------------
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";

    glewInit();

    // Create window with graphics context
    GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
    int Width = glfwGetVideoMode(Monitor)->width;
    int Height = glfwGetVideoMode(Monitor)->height;

    //int to center mouse
    int mouseposx = Width / 2;
    int mouseposy = Height / 2;


    glfwWindowHint(GLFW_FLOATING, true);
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_MAXIMIZED, true);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "AssaultBytes", NULL, NULL);
    if (window == NULL) {
        return 1;
    }

    glfwSetWindowAttrib(window, GLFW_DECORATED, false);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //imgui---------------------------------------------------------------------------------------------------------
    //imgui---------------------------------------------------------------------------------------------------------
    //imgui---------------------------------------------------------------------------------------------------------
    //imgui---------------------------------------------------------------------------------------------------------

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGuiStyle* style = &ImGui::GetStyle();

    style->FramePadding = ImVec2(8, 4);
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->FramePadding = ImVec2(8, 6);
    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 30, 30, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 30, 45, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 30, 45, 255);

    style->Colors[ImGuiCol_Button] = ImColor(255, 30, 45, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(240, 0, 0, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(120, 30, 45, 255);

    style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 30, 45, 255);
    style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 30, 45, 255);
    style->Colors[ImGuiCol_ScrollbarBg] = ImColor(255, 30, 45, 255);

    //MAIN LOOP---------------------------------------------------------------------------------------------
    //MAIN LOOP---------------------------------------------------------------------------------------------
    //MAIN LOOP---------------------------------------------------------------------------------------------
    //MAIN LOOP---------------------------------------------------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        if (GetAsyncKeyState(0x11) & 1) {
            if (menuVisible) {
                glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, true);
                menuVisible = false;
                SetCursorPos(mouseposx, mouseposy);
                Sleep(50);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

            }
            else {
                glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, false);
                menuVisible = true;
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(50);
                SetCursorPos(mouseposx, mouseposy);
            }


        }


        if (menuVisible) {
            ImGui::Begin("AssaultBytes V0.0 menu");

            if (ImGui::SliderInt("Player Speed", &playerspeed, 1, 10)) {
                DWORD curProtection;
                VirtualProtect((DWORD*)(localspeedCAVE), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                *localspeedCAVE = playerspeed;
                //if (!speedhackIni) {
                //    speedhackIni = true;
                //    finalhook(asmSpeed, 6, hookSpeedHack);
                //}
                if (playerspeed == 1) {
                    finalhook(asmSpeed, 6, unhookSpeedHack);
                }
                else {
                    finalhook(asmSpeed, 6, hookSpeedHack);
                }
            }
            if (ImGui::SliderFloat("Jump power", &jumpPower, 2, 10)) {
                DWORD curProtection;
                VirtualProtect((DWORD*)(localjumpPowerCAVE), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                *localjumpPowerCAVE = jumpPower;
                if (!jumppowerini) {
                    jumppowerini = true;
                    finalhook(asmSuperjump, 6, hookSuperjump);
                }
            }
            ImGui::Spacing();
            if (ImGui::Button("Enable radar hack")) {
                finalhook(asmMinimap, 6, hookminimap);
                finalhook(asmMap, 6, hookmap);
            }
            ImGui::Spacing();
            if (ImGui::Button("Disable radar hack")) {
                finalhook(asmMinimap, 6, unhookminimap);
                finalhook(asmMap, 6, unhookmap);
            }
            ImGui::Spacing();
            if (ImGui::Button("Enable fast reflexes")) {
                finalhook(asmMovility, 6, hookmovility);
            }
            ImGui::Spacing();
            if (ImGui::Button("Disable fast reflexes")) {
                finalhook(asmMovility, 6, unhookmovility);
            }
            ImGui::Spacing();
            if (ImGui::Button("Enable accuracy mode")) {
                DWORD curProtection;
                VirtualProtect((DWORD*)(localRecoilMultiplier), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                VirtualProtect((DWORD*)(localKickMultiplier), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                *localRecoilMultiplier = 0;
                *localKickMultiplier = 0;
            }
            ImGui::Spacing();
            if (ImGui::Button("Disable accuracy mode")) {
                DWORD curProtection;
                VirtualProtect((DWORD*)(localRecoilMultiplier), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                VirtualProtect((DWORD*)(localKickMultiplier), 32, PAGE_EXECUTE_READWRITE, &curProtection);
                *localRecoilMultiplier = 0.001000000047;
                *localKickMultiplier = -0.009999999776;
            }
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
