#pragma once
#include "pgr.h"

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glut.h"
#include "imgui/imgui_impl_opengl3.h"

Window* window;

void DisplayFn() {
    Renderer::Get().Render();
}

void TimerFn(int previousTime) {
    glutPostRedisplay();
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 0);
    Renderer::Get().Update();
    window->Update();
}

void KeyboardFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyPressedCallback(key);
    ImGui_ImplGLUT_KeyboardFunc(key, x, y);
}

void KeyboardUpFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyReleasedCallback(key);
    ImGui_ImplGLUT_KeyboardUpFunc(key, x, y);
}

void SpecialFn(int key, int x, int y) {
    InputManager::Get().SpecialPressedCallback(key);
    ImGui_ImplGLUT_SpecialFunc(key, x, y);
}

void SpecialUpFn(int key, int x, int y) {
    InputManager::Get().SpecialReleasedCallback(key);
    ImGui_ImplGLUT_SpecialUpFunc(key, x, y);
}

void PassiveMotionFn(int x, int y) {
    InputManager::Get().MouseCallback(x, y);
    ImGui_ImplGLUT_MotionFunc(x, y);
}

void MouseFn(int button, int state, int x, int y) {
    InputManager::Get().MouseClickCallback(button, state, x, y);
    ImGui_ImplGLUT_MouseFunc(button, state, x, y);
}

bool Init(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    if (!window->Init()) {
        std::cerr << "Failed to initialize the window" << std::endl;
        return false;
    }

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }

    glutReshapeFunc(ImGui_ImplGLUT_ReshapeFunc);
    glutDisplayFunc(DisplayFn);
    glutKeyboardFunc(KeyboardFn);
    glutKeyboardUpFunc(KeyboardUpFn);
    glutSpecialFunc(SpecialFn);
    glutSpecialUpFunc(SpecialUpFn);
    glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutPassiveMotionFunc(PassiveMotionFn);
    glutMouseFunc(MouseFn);
    
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 1);

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

    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}