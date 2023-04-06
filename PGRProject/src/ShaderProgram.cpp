#include "ShaderProgram.h"

glm::vec3 ShaderProgram::s_cameraPosition;

glm::vec3 ShaderProgram::s_pointLightPositions[MAX_POINT_LIGHTS];
int ShaderProgram::s_nextPointLightIndex;

glm::vec3 ShaderProgram::s_spotlightPositions[MAX_SPOTLIGHTS];
int ShaderProgram::s_nextSpotlightIndex;

bool ShaderProgram::CreateShader(const std::string& vs_source, const std::string& fs_source)
{
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

void ShaderProgram::UseShader()
{
    glUseProgram(m_programObject);
    if (m_shaderType == SHADER_TYPE_DEFAULT)
        glUniform1i(GetLocation("texDiffuse"), 0);
    CHECK_GL_ERROR();
}

bool ShaderProgram::Init()
{
    if (!LoadShaders()) {
        std::cerr << "Failed to load shaders" << std::endl;
        return false;
    }
    return true;
}

GLint ShaderProgram::GetLocation(std::string name)
{
    auto it = m_locations.find(name);
    if (it == m_locations.end())
        return 0;
    return m_locations.at(name);
}

bool ShaderProgram::LoadShaders()
{
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
    }

    CHECK_GL_ERROR();
    
    return true;
}

bool ShaderProgram::LoadDefault()
{
    ATTRIB_LOC("position");
    ATTRIB_LOC("normal");
    ATTRIB_LOC("texCoords");
    CHECK_GL_ERROR();

    UNIF_LOC("pvmMatrix");
    UNIF_LOC("localCameraPosition");
    CHECK_GL_ERROR();

    UNIF_LOC("colDiffuse");
    UNIF_LOC("texDiffuse");
    UNIF_LOC("useTexDiffuse");
    CHECK_GL_ERROR();

    UNIF_LOC("colSpecular");
    UNIF_LOC("specularExponent");
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
    return false;
}

bool ShaderProgram::LoadSkybox()
{
    ATTRIB_LOC("position");
    CHECK_GL_ERROR();

    UNIF_LOC("pvMatrix");
    CHECK_GL_ERROR();
    return false;
}

void ShaderProgram::InitPointLightLocations() {
    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        PL_LOC("color", i);
        PL_LOC("intensity", i);
        PL_LOC("position", i);
        PL_LOC("attenuation", i);
    }
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
}

void ShaderProgram::CreateUniformLocation(std::string cName, std::string shaderName) {
    GLint location = glGetUniformLocation(m_programObject, shaderName.c_str());
    m_locations.insert(std::pair<std::string, GLint>(cName, location));
}

void ShaderProgram::CreateAttributeLocation(std::string cName, std::string shaderName) {
    GLint location = glGetAttribLocation(m_programObject, shaderName.c_str());
    m_locations.insert(std::pair<std::string, GLint>(cName, location));
}


