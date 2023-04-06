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
	if (m_SpecialMap.at(GLUT_KEY_F1))
		return 0;
	if (m_SpecialMap.at(GLUT_KEY_F2))
		return 1;
	if (m_SpecialMap.at(GLUT_KEY_F3))
		return 2;
	return -1;
}

void InputManager::KeyPressedCallback(unsigned char key) {
	m_KeyMap.insert_or_assign(key, true);
}

void InputManager::KeyReleasedCallback(unsigned char key) {
	m_KeyMap.insert_or_assign(key, false);
}

void InputManager::SpecialPressedCallback(int key) {
	m_SpecialMap.insert_or_assign(key, true);
}

void InputManager::SpecialReleasedCallback(int key) {
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
	}

	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_UP, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_DOWN, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_LEFT, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_RIGHT, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_SHIFT_L, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_F1, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_F2, false));
	m_SpecialMap.insert(std::pair<int, bool>(GLUT_KEY_F3, false));

	m_WindowCenter = glm::vec2();
	m_WindowCenter.x = glutGet(GLUT_WINDOW_X) + glutGet(GLUT_WINDOW_WIDTH) / 2;
	m_WindowCenter.y = glutGet(GLUT_WINDOW_Y) + glutGet(GLUT_WINDOW_HEIGHT) / 2;
}
