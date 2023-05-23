//----------------------------------------------------------------------------------------
/**
 * \file       InputManager.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "InputManager.h"

glm::vec3 InputManager::RelativeVelocity() const {
	if (m_pickingMode) return glm::vec3(0.0f);
	int forward = (int)(m_keyMap.at('w') || (int)(m_keyMap.at('W')) || m_specialMap.at(GLUT_KEY_UP));
	int backwards = (int)(m_keyMap.at('s') || (int)(m_keyMap.at('S')) || m_specialMap.at(GLUT_KEY_DOWN));
	int left = (int)(m_keyMap.at('a') || (int)(m_keyMap.at('A')) || m_specialMap.at(GLUT_KEY_LEFT));
	int right = (int)(m_keyMap.at('d') || (int)(m_keyMap.at('D')) || m_specialMap.at(GLUT_KEY_RIGHT));
	int up = (int) m_keyMap.at(' ');
	int down = (int) m_specialMap.at(GLUT_KEY_SHIFT_L);
	return glm::vec3(right - left, up - down, backwards - forward);
}

glm::quat InputManager::CalculateRotation() {
	glm::vec3 euler = glm::vec3(glm::radians(-m_mousePos.y * c_mouseSensitivity), glm::radians(-m_mousePos.x * c_mouseSensitivity), 0.0f);
	return glm::quat(euler);
}

int InputManager::CameraToSwitch()
{
	if (m_specialReleasedMap.at(GLUT_KEY_F1)) {
		m_specialReleasedMap.insert_or_assign(GLUT_KEY_F1, false);
		return 0;
	}
	if (m_specialReleasedMap.at(GLUT_KEY_F2)) {
		m_specialReleasedMap.insert_or_assign(GLUT_KEY_F2, false);
		return 1;
	}
	if (m_specialReleasedMap.at(GLUT_KEY_F3)) {
		m_specialReleasedMap.insert_or_assign(GLUT_KEY_F3, false);
		return 2;
	}
	return -1;
}

int InputManager::ReadStencils() {
	return m_stencilValue;
}

void InputManager::KeyPressedCallback(unsigned char key) {
	m_keyMap.insert_or_assign(key, true);
}

void InputManager::KeyReleasedCallback(unsigned char key) {
	if (m_keyMap.at(key)) {
		m_keyReleasedMap.insert_or_assign(key, true);
	}
	m_keyMap.insert_or_assign(key, false);
}

void InputManager::SpecialPressedCallback(int key) {
	m_specialMap.insert_or_assign(key, true);
}

void InputManager::SpecialReleasedCallback(int key) {
	if (m_specialMap.at(key)) {
		m_specialReleasedMap.insert_or_assign(key, true);
	}
	m_specialMap.insert_or_assign(key, false);
}



void InputManager::MouseCallback(int x, int y) {
	if (!m_pickingMode) {
		m_mousePos.x += (x - m_windowCenter.x);
		m_mousePos.y += (y - m_windowCenter.y);
		m_mousePos.y = (m_mousePos.y > 90.0f / c_mouseSensitivity) ? 90.0f / c_mouseSensitivity : m_mousePos.y;
		m_mousePos.y = (m_mousePos.y < -90.0f / c_mouseSensitivity) ? -90.0f / c_mouseSensitivity : m_mousePos.y;
		glutWarpPointer(m_windowCenter.x, m_windowCenter.y);
	}
}

void InputManager::MouseClickCallback(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && !m_mouseState) {
		m_mouseState = true;
		unsigned char buf;
		glReadPixels(x, float(glutGet(GLUT_WINDOW_HEIGHT)) - y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &buf);
		m_stencilValue = buf;
	}
	else if (state == GLUT_UP && m_mouseState) {
		m_mouseState = false;
		m_stencilValue = -1;
	}
}

void InputManager::QueryWindowInput() {
	if (m_specialReleasedMap.at(GLUT_KEY_F4)) {
		m_specialReleasedMap.insert_or_assign(GLUT_KEY_F4, false);
		if (m_pickingMode) {
			m_pickingMode = false;
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(m_windowCenter.x, m_windowCenter.y);
		}
		else {
			m_pickingMode = true;
			glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
		}
	}
}

InputManager::InputManager() {
	for (unsigned char i = 0; i < 255; i++) {
		m_keyMap.insert(std::pair<unsigned char, bool>(i, false));
		m_keyReleasedMap.insert(std::pair<unsigned char, bool>(i, false));
	}
	std::vector<GLenum> keys = { GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT,
		GLUT_KEY_SHIFT_L, GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4 };

	for (auto e : keys) {
		m_specialMap.insert(std::pair<int, bool>(e, false));
		m_specialReleasedMap.insert(std::pair<int, bool>(e, false));
	}

	m_windowCenter = glm::vec2();
	m_windowCenter.x = float(glutGet(GLUT_SCREEN_WIDTH)) / 2.0f;
	m_windowCenter.y = float(glutGet(GLUT_SCREEN_HEIGHT)) / 2.0f;
}
