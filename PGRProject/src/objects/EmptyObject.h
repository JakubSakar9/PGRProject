#pragma once
#include "StaticObject.h"
#include "Object.h"

class EmptyObject :
	public ObjectInstance
{
public:
	EmptyObject() {}
	EmptyObject(const std::vector<WavefrontObject*>& sourceWavefront);
	EmptyObject(const std::string& name, bool useAssimp);
	~EmptyObject();

	void LoadAssimp(const std::string& filepath);

	void LoadCustom(const std::string& filepath);
};

