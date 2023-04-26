#pragma once

#include "Camera.h"
#include "EyeObject.h"
#include "PointLight.h"
#include "Rupee.h"
#include "Spotlight.h"
#include "StaticObject.h"
#include "Water.h"

class EmptyObject :
	public ObjectInstance
{
public:
	EmptyObject() {}
	EmptyObject(const std::vector<WavefrontObject*>& sourceWavefront);
	EmptyObject(nlohmann::json source);
	~EmptyObject();

	void LoadCustom(const std::string& filepath);

	void InitChildren(nlohmann::json source);
};

