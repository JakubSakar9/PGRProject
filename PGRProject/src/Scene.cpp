#include "Scene.h"
#include "objects/EmptyObject.h"

Scene::Scene()
{
    m_DynamicCamera = Camera(glm::vec3(0.0f, 10.0f, 350.0f), true);
    glm::vec3 lBound = glm::vec3(-80.0f, 11.0f, 250.0f);
    glm::vec3 uBound = glm::vec3(38.0f, 70.0f, 344.0f);
    m_DynamicCamera.ChangeBounds(lBound, uBound);
    m_StaticCamera1 = Camera(glm::vec3(0.0f, 10.0f, 350.0f), false);
    m_StaticCamera2 = Camera(glm::vec3(91.0f, 71.0f, 434.0f), false);
    m_ViewCamera = &m_DynamicCamera;
    m_RootModelMatrix = glm::mat4(1.0f);
}

bool Scene::Init()
{
    m_DynamicCamera.Init();
    m_StaticCamera1.Init();
    m_StaticCamera2.Init();

    m_rootObject = EmptyObject("Island", true);
    m_rootObject.GenObjects(SHADER_TYPE_DEFAULT);

    m_seaObject = EmptyObject("Sea", true);
    m_seaObject.GenObjects(SHADER_TYPE_DEFAULT);

    m_linkObject = EmptyObject("Link", true);
    m_linkObject.GenObjects(SHADER_TYPE_DEFAULT);
    m_linkObject.Scale(glm::vec3(4.0f));
    m_linkObject.Translate(glm::vec3(0.0f, 40.0f, 4000.0f));
    glm::vec3 linkColliderScale = glm::vec3(35.0f, 300.0f, 35.0f);
    m_linkObject.AddCollider(linkColliderScale);

    /*m_birdObject = EmptyObject("Kargaroc", true);
    m_birdObject.Scale(glm::vec3(400.0f));
    m_birdObject.Translate(glm::vec3(0.0f, 0.0f, 0.0f));
    m_birdObject.GenObjects(SHADER_TYPE_DEFAULT);*/

    m_RupeeObject = Rupee();
    m_RupeeObject.GenObjects(SHADER_TYPE_DEFAULT);
    
    m_skybox = Skybox();
    m_skybox.GenSkybox(SHADER_TYPE_SKYBOX);

    m_AmbientLight = AmbientLight(glm::vec3(.0f, .1f, .3f), .3f);
    m_DirectionalLight = DirectionalLight(glm::vec3(.2f, .3f, .6f), 1.5f, glm::vec3(0.1, -0.1, -0.5));

    glm::vec3 candle = glm::vec3(1.0f, 0.8f, 0.0f);
    glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
    m_pointLight1 = PointLight(candle, 0.4f, glm::vec3(30.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight2 = PointLight(candle, 0.4f, glm::vec3(20.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight3 = PointLight(candle, 0.4f, glm::vec3(10.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));
    m_pointLight4 = PointLight(candle, 0.4f, glm::vec3(-10.0f, 10.0f, 350.0f), glm::vec3(1.0f, 0.005f, 0.0f));

    m_spotlight1 = Spotlight(green, 1.0f, glm::vec3(0.0f, 10.0f, 370.0f), glm::vec3(1.0f, 0.005f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), 45.0f);
    m_spotlight2 = Spotlight(red, 1.0f, glm::vec3(14.0f, 15.0f, 373.0f), glm::vec3(1.0f, 0.001f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), 30.0f);
    CHECK_GL_ERROR();
    return true;
}

void Scene::Render()
{
    glm::mat4 viewMat = m_ViewCamera->ComputeViewMatrix();
    glm::mat4 projMat = m_ViewCamera->ComputeProjectionMatrix();
    m_seaObject.Draw(viewMat, projMat);
    m_rootObject.Draw(viewMat, projMat);
    m_linkObject.Draw(viewMat, projMat);
    //m_birdObject.Draw(viewMat, projMat);
    m_RupeeObject.Draw(viewMat, projMat);

    viewMat = m_ViewCamera->ComputeSkyboxViewMatrix();
    m_skybox.Draw(viewMat, projMat);
    glBindVertexArray(0);
}

void Scene::Update(float deltaTime)
{
    SwitchCamera();
    m_rootObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_seaObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_linkObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    //m_birdObject.Update(deltaTime, nullptr, m_ViewCamera->Position());
    m_RupeeObject.Update(deltaTime, nullptr, m_ViewCamera->Position());

    m_AmbientLight.Update(deltaTime);
    CHECK_GL_ERROR();
    m_DirectionalLight.Update(deltaTime);
    CHECK_GL_ERROR();

    m_pointLight1.Update(deltaTime);
    m_pointLight2.Update(deltaTime);
    m_pointLight3.Update(deltaTime);
    m_pointLight4.Update(deltaTime);

    m_spotlight1.Update(deltaTime);
    m_spotlight2.Update(deltaTime);
    CHECK_GL_ERROR();

    std::vector<BoxCollider*> colliders;
    m_linkObject.UpdateColliders(colliders);
    m_ViewCamera->Update(colliders, deltaTime);
}

void Scene::SwitchCamera() {
    int cameraID = InputManager::Get().CameraToSwitch();
    switch (cameraID) {
    case 0:
        m_ViewCamera = &m_DynamicCamera;
        break;
    case 1:
        m_ViewCamera = &m_StaticCamera1;
        break;
    case 2:
        m_ViewCamera = &m_StaticCamera2;
        break;
    }
}
