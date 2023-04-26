#include "Scene.h"
#include "objects/EmptyObject.h"

Scene* Scene::s_usedScene;

Scene::Scene(std::string name) {
    using json = nlohmann::json;
    std::ifstream f(std::string("data/scenes/") + name);
    json data = json::parse(f);

    m_AmbientLight = AmbientLight(data["ambientLight"]);
    m_DirectionalLight = DirectionalLight(data["directionalLight"]);

    m_rootObject = EmptyObject(data["objects"]);

    m_selectedCamera = 0;

    s_usedScene = this;
}

bool Scene::Init()
{
    m_rootObject.GenObjects();
    
    m_skybox = Skybox();
    m_skybox.GenSkybox();

    CHECK_GL_ERROR();
    return true;
}

void Scene::Render() {
    m_skybox.Draw();
    m_rootObject.Draw();
    glBindVertexArray(0);
}

void Scene::Update(float deltaTime)
{
    SwitchCamera();
    m_rootObject.Update(deltaTime, nullptr);

    m_AmbientLight.Update(deltaTime, nullptr);
    CHECK_GL_ERROR();
    m_DirectionalLight.Update(deltaTime, nullptr);
    CHECK_GL_ERROR();

    std::vector<BoxCollider*> colliders;
    m_rootObject.UpdateColliders(colliders);
    Camera::UpdateColliders(colliders);
}

void Scene::SwitchCamera() {
    int cameraCommand = InputManager::Get().CameraToSwitch();
    ShaderProgram::SwitchCamera(cameraCommand);
}
