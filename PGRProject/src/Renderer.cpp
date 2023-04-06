#include "Renderer.h"

bool Renderer::Init() {
    bool ret = true;
    ilInit();
    ret &= InitShaders();
    ret &= m_scene.Init(m_shaders);

    CHECK_GL_ERROR();
    
    m_lastTime = glutGet(GLUT_ELAPSED_TIME);

    glClearColor(.0f, .1f, .3f, 1.0f);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CHECK_GL_ERROR();
    return ret;
}

bool Renderer::InitShaders()
{
    bool ret = true;
    m_shaders.defaultShader->Init();
    m_shaders.skyboxShader->Init();
    return ret;
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_scene.Render(m_shaders);
    CHECK_GL_ERROR();
    glutSwapBuffers();
}

void Renderer::Update() {
    float deltaTime = glutGet(GLUT_ELAPSED_TIME) - m_lastTime;
    m_lastTime = glutGet(GLUT_ELAPSED_TIME);
    m_scene.Update(deltaTime, m_shaders);
    CHECK_GL_ERROR();
}
