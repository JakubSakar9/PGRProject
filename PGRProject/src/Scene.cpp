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
    m_LinkObject.Scale(glm::vec3(4.0f));
    m_LinkObject.Translate(glm::vec3(0.0f, 40.0f, 4000.0f));

    m_AmbientLight = AmbientLight(glm::vec3(.0f, .1f, .3f), .3f);
    m_DirectionalLight = DirectionalLight(glm::vec3(.2f, .3f, .6f), .7f, glm::vec3(0.5, -0.2, 0.1));
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

void Scene::Update(float deltaTime, ShaderProgram *shaderProgram)
{
    m_RootObject.Update(deltaTime, nullptr, m_ViewCamera.Position());
    m_SeaObject.Update(deltaTime, nullptr, m_ViewCamera.Position());
    m_LinkObject.Update(deltaTime, nullptr, m_ViewCamera.Position());

    m_AmbientLight.Update(shaderProgram);
    CHECK_GL_ERROR();
    m_DirectionalLight.Update(shaderProgram);

    m_ViewCamera.Update(shaderProgram, deltaTime);
}
