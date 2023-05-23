//----------------------------------------------------------------------------------------
/**
 * \file       Window.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "pgr.h"

#include "Renderer.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_X_OFFSET 80
#define DEFAULT_Y_OFFSET 80
#define DEFAULT_WINDOW_TITLE "PGR Application"

/// <summary>
/// A class that provides an abstraction layer for the GLUT window.
/// </summary>
class Window
{
private:
	/// <summary>
	/// Width of the window in pixels.
	/// </summary>
	int m_Width;

	/// <summary>
	/// Height of the window in pixels.
	/// </summary>
	int	m_Height;

	/// <summary>
	/// The x component of the position of the window in screen coordinates.
	/// </summary>
	int m_xOffset;

	/// <summary>
	/// The y component of the position of the window in screen coordinates.
	/// </summary>
	int m_yOffset;
	std::string m_Title;

public:
	/// <summary>
	/// Default constructor for the Window class.
	/// </summary>
	Window() {
		m_Width = DEFAULT_WINDOW_WIDTH;
		m_Height = DEFAULT_WINDOW_HEIGHT;
		m_xOffset = DEFAULT_X_OFFSET;
		m_yOffset = DEFAULT_Y_OFFSET;
		m_Title = DEFAULT_WINDOW_TITLE;
	}

	/// <summary>
	/// The window class constructor.
	/// </summary>
	/// <param name="width">- width of the window in pixels.</param>
	/// <param name="height">- height of the window in pixels.</param>
	/// <param name="title">- title of the window.</param>
	Window(int width, int height, const std::string& title)
		: m_Width(width), m_Height(height), m_Title(title) {
		m_xOffset = DEFAULT_X_OFFSET;
		m_yOffset = DEFAULT_Y_OFFSET;
	}
	
	/// <summary>
	/// The Window class constructor.
	/// </summary>
	/// <param name="width">- width of the window in pixels.</param>
	/// <param name="height">- height of the window in pixels.</param>
	/// <param name="xOffset">- the x component of the initial position of the window in screen coordinates.</param>
	/// <param name="yOffset">- the y component of the initial position of the window in screen coordinates.</param>
	/// <param name="title">- title of the window.</param>
	Window(int width, int height, int xOffset, int yOffset, const std::string& title)
		: m_Width(width), m_Height(height), m_xOffset(xOffset), m_yOffset(yOffset), m_Title(title) {}

	/// <summary>
	/// Initializes several parameters of the window using GLUT.
	/// </summary>
	/// <returns>Always true.</returns>
	bool Init();

	/// <summary>
	/// Checks if mode should be switched for each update iteration.
	/// </summary>
	void Update();
};

