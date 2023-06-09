//----------------------------------------------------------------------------------------
/**
 * \file       Window.cpp
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#include "Window.h"

bool Window::Init()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(m_xOffset, m_yOffset);
	glutInitWindowSize(m_Width, m_Height);
	glutCreateWindow(m_Title.c_str());
	glutFullScreen();
	glutSetCursor(GLUT_CURSOR_NONE);	
	return true;
}

void Window::Update() {
	InputManager::Get().QueryWindowInput();
}