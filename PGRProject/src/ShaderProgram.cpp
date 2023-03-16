#include "ShaderProgram.h"

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

    m_ProgramObject = pgr::createProgram({ vertexShader, fragmentShader});

    CHECK_GL_ERROR();
    
    if (m_ProgramObject == 0) {
        std::cerr << "Failed to create program" << std::endl;
        return false;
    }
    
    return true;
}

void ShaderProgram::UseShader()
{
    glUseProgram(m_ProgramObject);

    glUniform1i(locations.texDiffuse, 0);
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

bool ShaderProgram::LoadShaders()
{
    bool err = !CreateShader(DEFAULT_VS_SOURCE, DEFAULT_FS_SOURCE);
    if (err) {
        std::cerr << "Failed to create shader" << std::endl;
        return false;
    }

    // Attributes
    locations.position = glGetAttribLocation(m_ProgramObject, "position");
    locations.texCoords = glGetAttribLocation(m_ProgramObject, "texCoords");
    CHECK_GL_ERROR();

    // Uniforms
    locations.pvmMatrix = glGetUniformLocation(m_ProgramObject, "u_PVM");
    locations.texDiffuse = glGetUniformLocation(m_ProgramObject, "u_texDiffuse");
    CHECK_GL_ERROR();
    
    return true;
}
