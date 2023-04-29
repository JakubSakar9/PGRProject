#pragma once

#include "pgr.h"

#include "Renderer.h"

#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600
#define DEFAULT_X_OFFSET 80
#define DEFAULT_Y_OFFSET 80
#define DEFAULT_WINDOW_TITLE "PGR Application"

class Window
{
private:
	int m_Width, m_Height;
	int m_xOffset, m_yOffset;
	std::string m_Title;

public:
	Window() {
		m_Width = DEFAULT_WINDOW_WIDTH;
		m_Height = DEFAULT_WINDOW_HEIGHT;
		m_xOffset = DEFAULT_X_OFFSET;
		m_yOffset = DEFAULT_Y_OFFSET;
		m_Title = DEFAULT_WINDOW_TITLE;
	}

	Window(int width, int height, const std::string& title)
		: m_Width(width), m_Height(height), m_Title(title) {
		m_xOffset = DEFAULT_X_OFFSET;
		m_yOffset = DEFAULT_Y_OFFSET;
	}
	
	Window(int width, int height, int xOffset, int yOffset, const std::string& title)
		: m_Width(width), m_Height(height), m_xOffset(xOffset), m_yOffset(yOffset), m_Title(title) {}

	~Window() {}

	bool Init();

	void Update();
};

