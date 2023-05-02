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
	static InputManager s_instance;

	const float c_mouseSensitivity = 0.05;

	bool m_firstMouse = true;
	bool m_pickingMode = false;
	bool m_mouseState = false;

	int m_stencilValue = -1;

	std::map<unsigned char, bool> m_keyMap;
	std::map<int, bool> m_specialMap;
	std::map<unsigned char, bool> m_keyReleasedMap;
	std::map<int, bool> m_specialReleasedMap;
	
	glm::vec2 m_mousePos;
	glm::vec2 m_windowCenter;
	
	InputManager();
public:
	void KeyPressedCallback(unsigned char key);
	void KeyReleasedCallback(unsigned char key);
	void SpecialPressedCallback(int key);
	void SpecialReleasedCallback(int key);
	void MouseCallback(int x, int y);
	void MouseClickCallback(int button, int state, int x, int y);
	void QueryWindowInput();

	glm::vec3 RelativeVelocity() const;
	glm::quat CalculateRotation();
	int CameraToSwitch();
	int ReadStencils();
	bool IsGuiVisible() {
		return m_pickingMode;
	}
};

