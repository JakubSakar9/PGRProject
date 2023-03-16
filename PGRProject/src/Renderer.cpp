#include "Renderer.h"

bool Renderer::Init() {
    ilInit();
    m_ShaderProgram.Init();
    m_Scene.Init(&m_ShaderProgram);

    CHECK_GL_ERROR();
    
    m_LastTime = glutGet(GLUT_ELAPSED_TIME);

    glClearColor(0.02f, 0.53f, 0.95f, 1.0f);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    CHECK_GL_ERROR();
    return true;
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_Scene.Render(&m_ShaderProgram);
    CHECK_GL_ERROR();
    glutSwapBuffers();
}

void Renderer::Update() {
    float deltaTime = glutGet(GLUT_ELAPSED_TIME) - m_LastTime;
    m_LastTime = glutGet(GLUT_ELAPSED_TIME);
    m_Scene.Update(deltaTime);
}
