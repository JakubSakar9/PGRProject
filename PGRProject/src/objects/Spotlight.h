#pragma once

#include "../utils/json.hpp"

#include "Light.h"

#define SL(at, idx) std::string("spotlights[") + std::to_string(idx) + std::string("].") + std::string(at)

class Spotlight :
    public Light
{
private:
    glm::vec3 m_attenuation;
    glm::vec3 m_direction;
    unsigned int m_id;
    float m_sizeDegrees;
public:
    Spotlight() {}
    Spotlight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation, glm::vec3 direction, float size);
    Spotlight(nlohmann::json source);
    ~Spotlight() {}

    void Update(float deltaTime);
};

