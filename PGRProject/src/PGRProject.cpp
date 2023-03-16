#pragma once
#include "pgr.h"

#include "Window.h"
#include "Renderer.h"
#include "InputManager.h"

Window* window;

void DisplayFn() {
    Renderer::Get().Render();
}

void TimerFn(int previousTime) {
    glutPostRedisplay();
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 0);
    Renderer::Get().Update();
}

void ReshapeFn(int w, int h) {
    glViewport(0, 0, w, h);
}

void KeyboardFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyPressedCallback(key);
}

void KeyboardUpFn(unsigned char key, int x, int y) {
    InputManager::Get().KeyReleasedCallback(key);
}

void SpecialFn(int key, int x, int y) {
    InputManager::Get().SpecialPressedCallback(key);
}

void SpecialUpFn(int key, int x, int y) {
    InputManager::Get().SpecialReleasedCallback(key);
}

void PassiveMotionFn(int x, int y) {
    InputManager::Get().MouseCallback(x, y);
}

bool Init(int argc, char** argv) {
    glutInit(&argc, argv);

    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    if (!window->Init()) {
        std::cerr << "Failed to initialize the window" << std::endl;
        return false;
    }

    glutReshapeFunc(ReshapeFn);
    glutDisplayFunc(DisplayFn);
    glutKeyboardFunc(KeyboardFn);
    glutKeyboardUpFunc(KeyboardUpFn);
    glutSpecialFunc(SpecialFn);
    glutSpecialUpFunc(SpecialUpFn);
    glutPassiveMotionFunc(PassiveMotionFn);
    glutTimerFunc(Renderer::Get().RefreshTimeMs(), TimerFn, 1);

    if (!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR)) {
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");
    }
    
    return Renderer::Get().Init();
}

int main(int argc, char** argv) {
    window = new Window(1920, 1080, "PGR Project");
    if (!Init(argc, argv)) {
        pgr::dieWithError("Failed to initialize the application");
    }

    glutMainLoop();
}