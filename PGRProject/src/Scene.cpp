#include "Scene.h"
#include "objects/EmptyObject.h"

Scene::Scene()
{
    m_DynamicCamera = Camera(glm::vec3(0.0f, 10.0f, 350.0f), true);
    m_StaticCamera1 = Camera(glm::vec3(0.0f, 10.0f, 350.0f), false);
    m_ViewCamera = &m_DynamicCamera;
    m_RootModelMatrix = glm::mat4(1.0f);
}

bool Scene::Init(ShaderProgram *shaderProgram)
{
    m_DynamicCamera.Init();
    m_StaticCamera1.Init();
    m_StaticCamera2.Init();
    m_RootObject = EmptyObject("Island", true);
    m_RootObject.GenObjects(shaderProgram);
    m_SeaObject = EmptyObject("Sea", true);
    m_SeaObject.GenObjects(shaderProgram);
    m_LinkObject = EmptyObject("Link", true);
    m_LinkObject.GenObjects(shaderProgram);
    m_LinkObject.Scale(glm::vec3(4.0f));
    m_LinkObject.Translate(glm::vec3(0.0f, 40.0f, 4000.0f));
    m_RupeeObject = Rupee();
    m_RupeeObject.GenObjects(shaderProgram);

    m_AmbientLight = AmbientLight(glm::vec3(.0f, .1f, .3f), .3f);
    m_DirectionalLight = DirectionalLight(glm::vec3(.2f, .3f, .6f), .7f, glm::vec3(0.5, -0.2, 0.1));

    glm::vec3 candle = glm::vec3(1.0f, 0.8f, 0.0f);
    m_pointLight1 = PointLight(candle, 1.0f, glm::vec3(30.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight2 = PointLight(candle, 1.0f, glm::vec3(20.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight3 = PointLight(candle, 1.0f, glm::vec3(10.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight4 = PointLight(candle, 1.0f, glm::vec3(-10.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    CHECK_GL_ERROR();
    return true;
}

void Scene::Render(ShaderProgram *shaderProgram)
{
    glm::mat4 viewMat = m_ViewCamera->ComputeViewMatrix();
    glm::mat4 projMat = m_ViewCamera->ComputeProjectionMatrix();
    m_SeaObject.Draw(projMat, viewMat, shaderProgram);
    m_RootObject.Draw(projMat, viewMat, shaderProgram);
    m_LinkObject.Draw(projMat, viewMat, shaderProgram);
    m_RupeeObject.Draw(projMat, viewMat, shaderProgram);
    glBindVertexArray(0);
}

void Scene::Update(float deltaTime, ShaderProgram *shaderProgram)
{
    m_RootObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_SeaObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_LinkObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_RupeeObject.Update(deltaTime, nullptr, m_ViewCamera->Position());

    m_AmbientLight.Update(shaderProgram);
    CHECK_GL_ERROR();
    m_DirectionalLight.Update(shaderProgram);
    CHECK_GL_ERROR();

    m_pointLight1.Update(shaderProgram);
    m_pointLight2.Update(shaderProgram);
    m_pointLight3.Update(shaderProgram);
    m_pointLight4.Update(shaderProgram);
    CHECK_GL_ERROR();

    m_ViewCamera->Update(shaderProgram, deltaTime);
}
