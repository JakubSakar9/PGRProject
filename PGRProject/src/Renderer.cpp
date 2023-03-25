#include "Renderer.h"

bool Renderer::Init() {
    ilInit();
    m_ShaderProgram.Init();
    m_Scene.Init(&m_ShaderProgram);

    CHECK_GL_ERROR();
    
    m_LastTime = glutGet(GLUT_ELAPSED_TIME);

    glClearColor(.0f, .1f, .3f, 1.0f);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
