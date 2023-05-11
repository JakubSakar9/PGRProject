#pragma once

#include "../utils/json.hpp"

#include "Light.h"

#define SL(at, idx) std::string("spotlights[") + std::to_string(idx) + std::string("].") + std::string(at)

/// <summary>
/// A class for a light source that illuminates the scene from a single point and the space it illuminates has a conical shape.
/// </summary>
class Spotlight :
    public Light
{
private:
    /// <summary>
    /// A 3D vector that contains coefficients of the illumination function.
    /// Because the attenuation function that was used in this program was quadratic, the first coefficient is constant, the second coefficient is linear and the third coefficient is quadratic.
    /// </summar
    glm::vec3 m_attenuation;

    /// <summary>
    /// A 3D vector that describes the direction that the conical space points towards. Its magnitude has no influence on the scene illumination with the exception of the zero vector.
    /// </summary>
    glm::vec3 m_direction;

    /// <summary>
    /// A unique identifier for the spotlight, which is used by shaders.
    /// </summary>
    unsigned int m_id;

    /// <summary>
    /// Describes the angle of the conical shape.
    /// </summary>
    float m_sizeDegrees;
public:
    /// <summary>
    /// Default constructor for the Spotlight class. Do not use.
    /// </summary>
    Spotlight() {}

    /// <summary>
    /// The Spotlight class constructor. Suitable for debugging.
    /// </summary>
    /// <param name="color">- light color in RGB format. All of its elements range between zero and one.</param>
    /// <param name="intensity">- intensity of the directional light. It is used to scale the impact of the ambient light in the scene.</param>
    /// <param name="position">- local position of the light source.</param>
    /// <param name="attenuation">- coefficients of the quadratic attenuation function.</param>
    /// <param name="direction">- direction that the conical shape faces.</param>
    /// <param name="size">- angle of the conical shape in degrees.</param>
    Spotlight(glm::vec3 color, float intensity, glm::vec3 position, glm::vec3 attenuation, glm::vec3 direction, float size);

    /// <summary>
    /// The Spotlight class constructor. Used to load the spotlight from a JSON file.
    /// </summary>
    /// <param name="source">- JSON object that contains the spotlight data.</param>
    Spotlight(nlohmann::json source);

    /// <summary>
    /// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
    /// </summary>
    /// <param name="deltaTime">- elapsed time from the last frame.</param>
    /// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
    /// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
    void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation) override;

    /// <summary>
    /// Generates ImGui objects that will display properties of the object
    /// </summary>
    void ShowProperties() override;
};

