#pragma once

#include <iostream>
#include <map>

#include "pgr.h";

/// <summary>
/// A class that manages all user input that should affect the scene. This class does not manage input that is processed by the ImGUI library.
/// </summary>
class InputManager
{
public:
	/// <summary>
	/// Getter for the singleton instance of the InputManager class.
	/// </summary>
	/// <returns>An input manager instance.</returns>
	static InputManager& Get() {
		static InputManager instance;
		return instance;
	}
private:
	/// <summary>
	/// Holds the singleton instance of the InputManager class
	/// </summary>
	static InputManager s_instance;

	/// <summary>
	/// A constant that determines camera rotation in degrees that is performed when mouse is moved by one pixel.
	/// </summary>
	const float c_mouseSensitivity = 0.05;

	/// <summary>
	/// A flag that is used to mark the first iteration of the user input update in order to achieve deterministic mouse position when the program is started.
	/// </summary>
	bool m_firstMouse = true;

	/// <summary>
	/// A flag that is set to true if GUI is enabled. If GUI is enabled, object picking is enabled as well while active camera movement is disabled.
	/// </summary>
	bool m_pickingMode = false;

	/// <summary>
	/// Helper flag to detect mouse presses and releases.
	/// </summary>
	bool m_mouseState = false;

	/// <summary>
	/// Stores the value of the stencil buffer for the pixel that has last been clicked.
	/// </summary>
	int m_stencilValue = -1;

	/// <summary>
	/// Contains a map that says if each character key is currently pressed or not.
	/// </summary>
	std::map<unsigned char, bool> m_keyMap;

	/// <summary>
	/// Contains a map that says if several select special keys are currently pressed or not.
	/// </summary>
	std::map<int, bool> m_specialMap;

	/// <summary>
	/// Contains a map that says if each character key has just been released or not. 
	/// </summary>
	std::map<unsigned char, bool> m_keyReleasedMap;

	/// <summary>
	/// Contains a map that says if several select special keys have just been released or not.
	/// </summary>
	std::map<int, bool> m_specialReleasedMap;
	
	/// <summary>
	/// A 2D vector that keeps track of virtual mouse position, which is then used to calculate camera orientation.
	/// </summary>
	glm::vec2 m_mousePos;

	/// <summary>
	/// A 2D vector which is used to compute offset of mouse movement for each frame. Defines the position where the cursor is warped if mouse is used to control the camera.
	/// </summary>
	glm::vec2 m_windowCenter;
	
	/// <summary>
	/// The constructor for the InputManager class. Defines the set of used special keys and initializes key input maps.
	/// </summary>
	InputManager();
public:
	/// <summary>
	/// A callback that is called when a character key is pressed on the keyboard.
	/// </summary>
	/// <param name="key">- character that represents the pressed key.</param>
	void KeyPressedCallback(unsigned char key);

	/// <summary>
	/// A callback that is called when a character key is released on the keyboard.
	/// </summary>
	/// <param name="key">- character that represents the pressed key.</param>
	void KeyReleasedCallback(unsigned char key);

	/// <summary>
	/// A callback that is called when a special key is pressed on the keyboard.
	/// </summary>
	/// <param name="key">- key code that represents the pressed key.</param>
	void SpecialPressedCallback(int key);

	/// <summary>
	/// A callback that is called when a special key is released on the keyboard.
	/// </summary>
	/// <param name="key">- key code that represents the pressed key.</param>
	void SpecialReleasedCallback(int key);

	/// <summary>
	/// A callback that is called whenever mouse is moved.
	/// </summary>
	/// <param name="x">- new position of the mouse in the x axis.</param>
	/// <param name="y">- new position of the mouse in the y axis.</param>
	void MouseCallback(int x, int y);

	/// <summary>
	/// A callback that is called whenever one of the mouse buttons is clicked or released.
	/// </summary>
	/// <param name="button">- code of the clicked button.</param>
	/// <param name="state">- state of the mouse button. Either GLUT_UP or GL_DOWN.</param>
	/// <param name="x">- position of the mouse when the click was initiated in the x axis.</param>
	/// <param name="y">- position of the mouse when the click was initiated in the y axis.</param>
	void MouseClickCallback(int button, int state, int x, int y);

	/// <summary>
	/// Queries input manager for the mode switch key, 'F4'.
	/// </summary>
	void QueryWindowInput();

	/// <summary>
	/// Computes velocity of the camera based on the user input. This velocity is not the final velocity and will be further multiplied by camera speed, which may be different for each camera
	/// </summary>
	/// <returns></returns>
	glm::vec3 RelativeVelocity() const;

	/// <summary>
	/// Computes new rotation of the camera based on the virtual mouse position.
	/// </summary>
	/// <returns></returns>
	glm::quat CalculateRotation();

	/// <summary>
	/// Returns a command that is used to switch cameras based on the user input.
	/// </summary>
	/// <returns>
	/// A code that represents a command, which can have four different values.
	/// <list type="bullet">
	///		<item>0 - F1 was pressed</item>
	///		<item>1 - F2 was pressed</item>
	///		<item>2 - F3 was pressed</item>
	///		<item>-1 - none of the mentioned keys was pressed</item>
	///	</list>
	/// </returns>
	int CameraToSwitch();

	/// <summary>
	/// Reads the value in the stencil buffer for the current mouse position.
	/// </summary>
	/// <returns>The value in the stencil buffer.</returns>
	int ReadStencils();

	bool IsGuiVisible() {
		return m_pickingMode;
	}
};

