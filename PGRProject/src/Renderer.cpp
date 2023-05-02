#include "Renderer.h"

bool Renderer::Init() {
    bool ret = true;
    ret &= InitShaders();
    ret &= m_scene.Init();
    CHECK_GL_ERROR();

    m_scene.Init();
    
    m_lastTime = glutGet(GLUT_ELAPSED_TIME);

    glClearColor(.0f, .1f, .3f, 1.0f);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    CHECK_GL_ERROR();
    return ret;
}

bool Renderer::InitShaders()
{
    bool ret = true;
    for (int st = 0; st != SHADER_TYPE_N; st++) {
        ShaderProgram::GetShader((ShaderType) st)->Init();
    }
    ShaderProgram::GetShader(SHADER_TYPE_DEFAULT)->InitLights();
    ShaderProgram::GetShader(SHADER_TYPE_WATER)->InitLights();
    return ret;
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    m_scene.Render();
    CHECK_GL_ERROR();
    RenderGui();
    glutSwapBuffers();
}

void Renderer::Update() {
    float deltaTime = glutGet(GLUT_ELAPSED_TIME) - m_lastTime;
    m_lastTime = glutGet(GLUT_ELAPSED_TIME);
    m_scene.Update(deltaTime);
    CHECK_GL_ERROR();
}

void Renderer::RenderGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO();
    CHECK_GL_ERROR();

    if (InputManager::Get().IsGuiVisible()) {
        
        ImGui::Begin("Scene graph", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        m_scene.RenderGraph();
        ImGui::End();

        //SetCursorPos();
        ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        m_scene.ShowProperties();
        ImGui::End();
    }
    CHECK_GL_ERROR();

    ImGui::Render();
    CHECK_GL_ERROR();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    CHECK_GL_ERROR();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    CHECK_GL_ERROR();
}

Renderer::Renderer() {
    m_refreshRate = DEFAULT_REFRESH_RATE;
    m_lastTime = 0;
        m_refreshTimeMs = 1000.0f / m_refreshRate;

    ShaderProgram* defaultShader = new ShaderProgram("Shaders/default-vs.glsl",
        "Shaders/default-fs.glsl", SHADER_TYPE_DEFAULT);

    ShaderProgram* skyboxShader = new ShaderProgram("Shaders/skybox-vs.glsl",
        "Shaders/skybox-fs.glsl", SHADER_TYPE_SKYBOX);

    ShaderProgram* eyeShader = new ShaderProgram("Shaders/eye-vs.glsl",
        "Shaders/eye-fs.glsl", SHADER_TYPE_EYE);
    
    ShaderProgram* waterShader = new ShaderProgram("Shaders/water-vs.glsl",
        "Shaders/water-fs.glsl", SHADER_TYPE_WATER);
    
    ResourceManager::Get().LoadMaterials();
    m_scene = Scene("outsetIsland.json");
}
