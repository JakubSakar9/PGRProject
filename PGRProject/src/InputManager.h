#pragma once

#include <iostream>
#include <map>

#include "pgr.h";

class InputManager
{
public:
	static InputManager& Get() {
		static InputManager instance;
		return instance;
	}
private:
	static InputManager s_Instance;

	const float c_MouseSensitivity = 0.05;

	bool m_FirstMouse = true;

	std::map<unsigned char, bool> m_KeyMap;
	std::map<int, bool> m_SpecialMap;
	
	glm::vec2 m_MousePos;
	glm::vec2 m_WindowCenter;
	
	InputManager();
public:
	void KeyPressedCallback(unsigned char key);
	void KeyReleasedCallback(unsigned char key);
	void SpecialPressedCallback(int key);
	void SpecialReleasedCallback(int key);
	void MouseCallback(int x, int y);

	glm::vec3 RelativeVelocity() const;
	glm::quat CalculateRotation();
	int CameraToSwitch();
};

