#pragma once

#include "Camera.h"
#include "EyeObject.h"
#include "PointLight.h"
#include "Rupee.h"
#include "Spotlight.h"
#include "StaticObject.h"
#include "Water.h"
#include "utils/Circle.h"

class EmptyObject :
	public ObjectInstance
{
private:
	AnimationCurve* m_curve = nullptr;
	float m_time;

	glm::mat4 ComputeModelMatrix(float time);
public:
	EmptyObject() {}
	EmptyObject(const std::vector<WavefrontObject*>& sourceWavefront);
	EmptyObject(nlohmann::json source);
	~EmptyObject();

	void LoadCustom(const std::string& filepath);

	void InitChildren(nlohmann::json source);

	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);
};

