#include "InputManager.h"

glm::vec3 InputManager::RelativeVelocity() const {
	int forward = (int)(m_KeyMap.at('w') || m_SpecialMap.at(GLUT_KEY_UP));
	int backwards = (int)(m_KeyMap.at('s') || m_SpecialMap.at(GLUT_KEY_DOWN));
	int left = (int)(m_KeyMap.at('a') || m_SpecialMap.at(GLUT_KEY_LEFT));
	int right = (int)(m_KeyMap.at('d') || m_SpecialMap.at(GLUT_KEY_RIGHT));
	int up = (int) m_KeyMap.at(' ');
	int down = (int) m_SpecialMap.at(GLUT_KEY_SHIFT_L);
	return glm::vec3(right - left, up - down, backwards - forward);
}

glm::quat InputManager::CalculateRotation() {
	
	glm::vec3 euler = glm::vec3(glm::radians(-m_MousePos.y * c_MouseSensitivity), glm::radians(-m_MousePos.x * c_MouseSensitivity), 0.0f);
	return glm::quat(euler);
}

int InputManager::CameraToSwitch()
{
	if (m_SpecialReleasedMap.at(GLUT_KEY_F1)) {
		m_SpecialReleasedMap.insert_or_assign(GLUT_KEY_F1, false);
		return 0;
	}
	if (m_SpecialReleasedMap.at(GLUT_KEY_F2)) {
		m_SpecialReleasedMap.insert_or_assign(GLUT_KEY_F2, false);
		return 1;
	}
	if (m_SpecialReleasedMap.at(GLUT_KEY_F3)) {
		m_SpecialReleasedMap.insert_or_assign(GLUT_KEY_F3, false);
		return 2;
	}
	return -1;
}

void InputManager::KeyPressedCallback(unsigned char key) {
	m_KeyMap.insert_or_assign(key, true);
}

void InputManager::KeyReleasedCallback(unsigned char key) {
	if (m_KeyMap.at(key)) {
		m_KeyReleasedMap.insert_or_assign(key, true);
	}
	m_KeyMap.insert_or_assign(key, false);
}

void InputManager::SpecialPressedCallback(int key) {
	m_SpecialMap.insert_or_assign(key, true);
}

void InputManager::SpecialReleasedCallback(int key) {
	if (m_SpecialMap.at(key)) {
		m_SpecialReleasedMap.insert_or_assign(key, true);
	}
	m_SpecialMap.insert_or_assign(key, false);
}



void InputManager::MouseCallback(int x, int y) {
	m_MousePos.x += (x - m_WindowCenter.x);
	m_MousePos.y += (y - m_WindowCenter.y);
	m_MousePos.y = (m_MousePos.y >  90.0f / c_MouseSensitivity) ?  90.0f / c_MouseSensitivity : m_MousePos.y;
	m_MousePos.y = (m_MousePos.y < -90.0f / c_MouseSensitivity) ? -90.0f / c_MouseSensitivity : m_MousePos.y;
	glutWarpPointer(m_WindowCenter.x, m_WindowCenter.y);
}

InputManager::InputManager() {
	for (unsigned char i = 0; i < 255; i++) {
		m_KeyMap.insert(std::pair<unsigned char, bool>(i, false));
		m_KeyReleasedMap.insert(std::pair<unsigned char, bool>(i, false));
	}
	std::vector<GLenum> keys = { GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT,
		GLUT_KEY_SHIFT_L, GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3 };

	for (auto e : keys) {
		m_SpecialMap.insert(std::pair<int, bool>(e, false));
	}
	for (auto e : keys) {
		m_SpecialReleasedMap.insert(std::pair<int, bool>(e, false));
	}

	m_WindowCenter = glm::vec2();
	m_WindowCenter.x = glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2;
	m_WindowCenter.y = glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2;
}
