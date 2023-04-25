#include "EmptyObject.h"

EmptyObject::EmptyObject(const std::vector<WavefrontObject*>& sourceWavefront) {
	// Not yet implemented
}

EmptyObject::EmptyObject(nlohmann::json source) {
	InitTransform(source);
	InitChildren(source);
}

EmptyObject::~EmptyObject() {
	ObjectInstance::~ObjectInstance();
}

void EmptyObject::LoadCustom(const std::string& filepath) {
}

void EmptyObject::InitChildren(nlohmann::json source) {
	using json = nlohmann::json;
	for (json c : source["children"]) {
		if (c["type"] == "static") {
			m_children.push_back(new StaticObject(c));
		}
		else if (c["type"] == "empty") {
			m_children.push_back(new EmptyObject(c));
		}
		else if (c["type"] == "eye") {
			m_children.push_back(new EyeObject(c));
		}
		else if (c["type"] == "rupee") {
			m_children.push_back(new Rupee(c));
		}
		else if (c["type"] == "pointLight") {
			PointLight* pl = new PointLight(c);
			m_children.push_back(pl);
		}
		else if (c["type"] == "spotlight") {
			Spotlight* sl = new Spotlight(c);
			m_children.push_back(sl);
		}
		else if (c["type"] == "camera") {
			Camera* cam = new Camera(c);
			m_children.push_back(cam);
		}
		else {
			std::cerr << "Invalid object type" << std::endl;
		}
	}
}
