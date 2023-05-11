#pragma once
#include "pgr.h"

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl3.h"

Window* window;

/// <summary>
/// The display function that is called by GLUT.
/// </summary>
void DisplayFn() {
    Renderer::Get().Render();
}

/// <summary>
/// The timer function that is called by GLUT.
/// </summary>
/// <param name="previousTime">- time parameter used by GLUT.</param>
void TimerFn(int previousTime) {
    glutPostRedisplay();
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 0);
    Renderer::Get().Update();
    window->Update();
}

/// <summary>
/// The keyboard function used by GLUT.
/// </summary>
/// <param name="key">- the key that was pressed.</param>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void KeyboardFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyPressedCallback(key);
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}

/// <summary>
/// The keyboard up function used by GLUT.
/// </summary>
/// <param name="key">- the key that was released.</param>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void KeyboardUpFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyReleasedCallback(key);
    ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}


/// <summary>
/// The special function used by GLUT.
/// </summary>
/// <param name="key">- the key that was pressed.</param>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void SpecialFn(int key, int x, int y) {
    InputManager::Get().SpecialPressedCallback(key);
    ImGui_ImplGLUT_SpecialFunc(key, x, y);
}

/// <summary>
/// The special up function used by GLUT.
/// </summary>
/// <param name="key">- the key that was released.</param>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void SpecialUpFn(int key, int x, int y) {
    InputManager::Get().SpecialReleasedCallback(key);
    ImGui_ImplGLUT_SpecialUpFunc(key, x, y);
}

/// <summary>
/// The passive motion function used by GLUT.
/// </summary>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void PassiveMotionFn(int x, int y) {
    InputManager::Get().MouseCallback(x, y);
    ImGui_ImplGLUT_MotionFunc(x, y);
}


/// <summary>
/// The passive motion function used by GLUT.
/// </summary>
/// <param name="button">- code of the pressed/released mouse button.</param>
/// <param name="state">- information whether the button was pressed or released.</param>
/// <param name="x">- x component of the position of the mouse cursor.</param>
/// <param name="y">- y component of the position of the mouse cursor.</param>
void MouseFn(int button, int state, int x, int y) {
    InputManager::Get().MouseClickCallback(button, state, x, y);
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

/// <summary>
/// Function that initializes everything
/// </summary>
/// <param name="argc">- number of arguments used during execution.</param>
/// <param name="argv">- arguments used during execution.</param>
/// <returns></returns>
bool Init(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    if (!window->Init()) {
        std::cerr << "Failed to initialize the window" << std::endl;
        return false;
    }
    std::cerr << "INFO: Window initialized" << std::endl;

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    std::cerr << "INFO: PGR initialized" << std::endl;

    glutReshapeFunc(ImGui_ImplGLUT_ReshapeFunc);
    glutDisplayFunc(DisplayFn);
    glutKeyboardFunc(KeyboardFn);
    glutKeyboardUpFunc(KeyboardUpFn);
    glutSpecialFunc(SpecialFn);
    glutSpecialUpFunc(SpecialUpFn);
    glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutPassiveMotionFunc(PassiveMotionFn);
    glutMouseFunc(MouseFn);
    std::cerr << "INFO: Input callbacks set" << std::endl;
    
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 1);
    std::cerr << "INFO: Timer function set" << std::endl;

    //ImGui init
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();
    
    return Renderer::Get().Init();
}

int main(int argc, char** argv) {
    window = new Window(1920, 1080, "Outset Island");
    if (!Init(argc, argv)) {
        pgr::dieWithError("Failed to initialize the application");
    }
    std::cout << "Launching main loop" << std::endl;

    glutMainLoop();

    std::cout << "Main loop over" << std::endl;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}