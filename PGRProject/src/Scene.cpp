//----------------------------------------------------------------------------------------
/**
 * \file       Scene.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

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
    m_rootObject.GenObjects(m_transparentObjects);
    
    m_skybox = Skybox();
    m_skybox.GenSkybox();

    CHECK_GL_ERROR();
    return true;
}

void Scene::Render() {
    m_skybox.Draw();
    m_rootObject.Draw();
    RenderTransparent();
    glBindVertexArray(0);
}

void Scene::RenderTransparent() {
    std::sort(m_transparentObjects.begin(), m_transparentObjects.end(), [](ObjectInstance *o1, ObjectInstance *o2)
        {
            float d1 = glm::distance(o1->m_globalPosition, ShaderProgram::s_activeCameraPosition);
            float d2 = glm::distance(o2->m_globalPosition, ShaderProgram::s_activeCameraPosition);
            return d1 > d2;
        });

    for (ObjectInstance* o : m_transparentObjects) {
        o->Draw();
    }
}

void Scene::Update(float deltaTime) {
    SwitchCamera();
    m_rootObject.Update(deltaTime, nullptr, glm::quat());

    m_AmbientLight.Update(deltaTime, nullptr, glm::quat());
    CHECK_GL_ERROR();
    m_DirectionalLight.Update(deltaTime, nullptr, glm::quat());
    CHECK_GL_ERROR();

    std::vector<BoxCollider*> colliders;
    m_rootObject.UpdateColliders(colliders);
    Camera::UpdateColliders(colliders);
}

void Scene::SwitchCamera() {
    int cameraCommand = InputManager::Get().CameraToSwitch();
    ShaderProgram::SwitchCamera(cameraCommand);
}

void Scene::RenderGraph() {
    m_AmbientLight.RenderGraph();
    m_DirectionalLight.RenderGraph();
    m_rootObject.RenderGraph();
}

void Scene::ShowProperties() {
    ObjectInstance* objPtr = m_rootObject.SelectObject();
    objPtr = objPtr ? objPtr : m_AmbientLight.SelectObject();
    objPtr = objPtr ? objPtr : m_DirectionalLight.SelectObject();
    m_selectedObject = (objPtr) ? objPtr : m_selectedObject;
    if (m_selectedObject)
        m_selectedObject->ShowProperties();
    else
        ImGui::Text("No object selected");
}
