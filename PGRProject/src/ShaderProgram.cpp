#include "ShaderProgram.h"

int ShaderProgram::s_nextPointLightIndex;
int ShaderProgram::s_nextSpotlightIndex;
int ShaderProgram::s_activeCameraIndex = 0;
int ShaderProgram::s_nextCameraIndex = 1;

std::map<ShaderType, ShaderProgram*> ShaderProgram::s_shaders;

bool ShaderProgram::CreateShader(const std::string& vs_source, const std::string& fs_source) {
    std::cerr << "Creating shaders..." << std::endl;
    GLuint vertexShader = pgr::createShaderFromFile(GL_VERTEX_SHADER, vs_source);
    GLuint fragmentShader = pgr::createShaderFromFile(GL_FRAGMENT_SHADER, fs_source);

    if (vertexShader == 0) {
        std::cerr << "Failed to create vertex shader" << std::endl;
        return false;
    }

    if (fragmentShader == 0) {
        std::cerr << "Failed to create fragment shader" << std::endl;
        return false;
    }

    m_programObject = pgr::createProgram({ vertexShader, fragmentShader});

    CHECK_GL_ERROR();
    
    if (m_programObject == 0) {
        std::cerr << "Failed to create program" << std::endl;
        return false;
    }
    
    return true;
}

void ShaderProgram::UseShader() {
    glUseProgram(m_programObject);
    CHECK_GL_ERROR();
}

bool ShaderProgram::Init() {
    if (!LoadShaders()) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }
    return true;
}

GLint ShaderProgram::GetLocation(std::string name) {
    auto it = m_locations.find(name);
    if (it == m_locations.end())
        return 0;
    return m_locations.at(name);
}

ShaderProgram* ShaderProgram::GetShader(ShaderType type) {
    return s_shaders.at(type);
}

void ShaderProgram::SwitchCamera(int command) {
    switch (command) {
    case 0:
        s_activeCameraIndex = 0;
        std::cout << "DEBUG: Switched to dynamic camera (0)" << std::endl;
        break;
    case 1:
        s_activeCameraIndex--;
        if (s_activeCameraIndex == -1) {
            s_activeCameraIndex = s_nextCameraIndex - 1;
        }
        std::cout << "DEBUG: Switched to camera " << s_activeCameraIndex << std::endl;
        break;
    case 2:
        s_activeCameraIndex++;
        if (s_activeCameraIndex == s_nextCameraIndex) {
            s_activeCameraIndex = 0;
        }
        std::cout << "DEBUG: Switched to camera " << s_activeCameraIndex << std::endl;
        break;
    }
}

int ShaderProgram::AddCamera() {
    s_nextCameraIndex++;
    return s_nextCameraIndex - 1;
}

bool ShaderProgram::LoadShaders() {
    bool err = !CreateShader(m_vertexShaderPath, m_fragmentShaderPath);
    if (err) {
        std::cerr << "Failed to create shader" << std::endl;
        return false;
    }

    switch (m_shaderType) {
    case SHADER_TYPE_DEFAULT:
        LoadDefault();
        break;
    case SHADER_TYPE_SKYBOX:
        LoadSkybox();
        break;
    case SHADER_TYPE_EYE:
        LoadEye();
        break;
    case SHADER_TYPE_WATER:
        LoadWater();
        break;
    }

    CHECK_GL_ERROR();
    
    return true;
}

bool ShaderProgram::LoadBasePBR()
{
    ATTRIB_LOC("position");
    ATTRIB_LOC("normal");
    ATTRIB_LOC("texCoords");
    CHECK_GL_ERROR();

    UNIF_LOC("pvMatrix");
    UNIF_LOC("mMatrix");
    UNIF_LOC("cameraPosition");
    CHECK_GL_ERROR();

    UNIF_LOC("colAlbedo");

    UNIF_LOC("colEmission");
    CHECK_GL_ERROR();

    UNIF_LOC("specular");
    CHECK_GL_ERROR();

    UNIF_LOC("roughness");
    CHECK_GL_ERROR();

    UNIF_LOC("transmission");
    CHECK_GL_ERROR();

    UNIF_LOC("ambientLight.color");
    UNIF_LOC("ambientLight.intensity");
    CHECK_GL_ERROR();

    UNIF_LOC("directionalLight.color");
    UNIF_LOC("directionalLight.direction");
    UNIF_LOC("directionalLight.intensity");
    CHECK_GL_ERROR();

    InitPointLightLocations();
    CHECK_GL_ERROR();

    InitSpotlightLocations();
    CHECK_GL_ERROR();
    return true;
}

bool ShaderProgram::LoadDefault() {
    LoadBasePBR();

    UNIF_LOC("texAlbedo");
    UNIF_LOC("useTexAlbedo");

    UNIF_LOC("texNormal");
    UNIF_LOC("useTexNormal");
    CHECK_GL_ERROR();
    return false;
}

bool ShaderProgram::LoadSkybox() {
    ATTRIB_LOC("position");
    CHECK_GL_ERROR();

    UNIF_LOC("pvMatrix");
    CHECK_GL_ERROR();
    return false;
}

bool ShaderProgram::LoadEye() {
    ATTRIB_LOC("position");
    ATTRIB_LOC("texCoords");
    CHECK_GL_ERROR();

    UNIF_LOC("texAlbedo");
    CHECK_GL_ERROR();

    UNIF_LOC("pvMatrix");
    UNIF_LOC("mMatrix");
    CHECK_GL_ERROR();

    UNIF_LOC("frameId");
    UNIF_LOC("numFrames");
    CHECK_GL_ERROR();
    return true;
}

bool ShaderProgram::LoadWater() {
    LoadBasePBR();

    UNIF_LOC("texNormal1");
    UNIF_LOC("texNormal2");
    
    UNIF_LOC("waveSpeed");
    UNIF_LOC("time");
    return true;
}

void ShaderProgram::InitPointLightLocations() {
    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        PL_LOC("color", i);
        PL_LOC("intensity", i);
        PL_LOC("position", i);
        PL_LOC("attenuation", i);
    }
    UNIF_LOC("numPointLights");
}

void ShaderProgram::InitSpotlightLocations() {
    for (int i = 0; i < MAX_SPOTLIGHTS; i++) {
        SL_LOC("color", i);
        SL_LOC("intensity", i);
        SL_LOC("position", i);
        SL_LOC("attenuation", i);
        SL_LOC("direction", i);
        SL_LOC("size", i);
    }
    UNIF_LOC("numSpotlights");
}

void ShaderProgram::CreateUniformLocation(std::string cName, std::string shaderName) {
    GLint location = glGetUniformLocation(m_programObject, shaderName.c_str());
    m_locations.insert(std::pair<std::string, GLint>(cName, location));
}

void ShaderProgram::CreateAttributeLocation(std::string cName, std::string shaderName) {
    GLint location = glGetAttribLocation(m_programObject, shaderName.c_str());
    m_locations.insert(std::pair<std::string, GLint>(cName, location));
}


