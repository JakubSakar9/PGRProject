#include "Scene.h"
#include "objects/EmptyObject.h"

Scene::Scene()
{
    m_ViewCamera = Camera(glm::vec3(0.0f, 10.0f, 350.0f));
    m_RootModelMatrix = glm::mat4(1.0f);
}

bool Scene::Init(ShaderProgram *shaderProgram)
{
    m_ViewCamera.Init();
    m_RootObject = EmptyObject("Island", true);
    m_RootObject.GenObjects(shaderProgram);
    m_SeaObject = EmptyObject("Sea", true);
    m_SeaObject.GenObjects(shaderProgram);
    m_LinkObject = EmptyObject("Link", true);
    m_LinkObject.GenObjects(shaderProgram);
    CHECK_GL_ERROR();
    return true;
}

void Scene::Render(ShaderProgram *shaderProgram)
{
    m_SeaObject.Draw(m_ViewCamera.ComputeViewMatrix(), m_ViewCamera.ComputeProjectionMatrix(), shaderProgram);
    m_RootObject.Draw(m_ViewCamera.ComputeViewMatrix(), m_ViewCamera.ComputeProjectionMatrix(), shaderProgram);
    m_LinkObject.Draw(m_ViewCamera.ComputeViewMatrix(), m_ViewCamera.ComputeProjectionMatrix(), shaderProgram);
    glBindVertexArray(0);
}

void Scene::Update(float deltaTime)
{
    m_RootObject.Update(deltaTime, &m_RootModelMatrix);
    m_SeaObject.Update(deltaTime, &m_RootModelMatrix);
    m_ViewCamera.Update(deltaTime);
}
