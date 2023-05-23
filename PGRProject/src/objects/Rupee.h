//----------------------------------------------------------------------------------------
/**
 * \file       Rupee.h
 * \author     Jakub Sakar
 * \date       2023/05/23
 *
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "StaticObject.h"

#include "../InputManager.h"

/// <summary>
/// Hardcoded array that contains positions, normals and texture coordinates of individual vertices in the rupee mesh.
/// </summary>
const float rupeeVertices[] = {
	  0.000,
	  1.60000002,
	  0,
	- 0.7294999,
	 0.54720002,
	 0.41040000,
	 0.75	   ,
	 0.625	   ,
	- 0.3000000,
	 1.20000005,
	 0		   ,
	- 0.7294999,
	 0.54720002,
	 0.41040000,
	 0.875	   ,
	 0.625	   ,
	- 0.3000000,
	 0.75	   ,
	 0.60000002,
	- 0.7294999,
	 0.54720002,
	 0.41040000,
	 0.875	   ,
	 0.750	   ,
	 0.000	   ,
	 1.000	   ,
	 0.80000001,
	- 0.7294999,
	 0.54720002,
	 0.41040000,
	 0.75	   ,
	 0.75	   ,
	 0		   ,
	- 1		   ,
	 0.80000001,
	- 0.5547000,
	 0		   ,
	 0.83209997,
	 0.375	   ,
	 0.875	   ,
	 0		   ,
	 1		   ,
	 0.80000001,
	- 0.5547000,
	 0		   ,
	 0.83209997,
	 0.625	   ,
	 0.875	   ,
	 - 0.300000,
	 0.75	   ,
	 0.60000002,
	- 0.5547000,
	 0		   ,
	 0.83209997,
	 0.625	   ,
	 1		   ,
	- 0.3000000,
	- 0.75	   ,
	 0.60000002,
	- 0.5547000,
	 0		   ,
	 0.83209997,
	 0.375	   ,
	 1		   ,
	- 0.3000000,
	- 1.2000000,
	 0		   ,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0.125	   ,
	- 0.3000000,
	 1.20000005,
	 0		   ,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0.125	   ,
	- 0.3000000,
	 0.75	   ,
	- 0.6000000,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0.25	   ,
	- 0.3000000,
	- 0.75	   ,
	- 0.6000000,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0.25	   ,
	 0		   ,
	- 1.6000000,
	 0		   ,
	 0.72949999,
	- 0.5472000,
	 0.41040000,
	 0.25	   ,
	 0.625	   ,
	 0.30000001,
	- 1.2000000,
	 0		   ,
	 0.72949999,
	- 0.5472000,
	 0.41040000,
	 0.375	   ,
	 0.625	   ,
	 0.30000001,
	- 0.75	   ,
	 0.60000002,
	 0.72949999,
	- 0.5472000,
	 0.41040000,
	 0.375	   ,
	 0.75	   ,
	 0		   ,
	- 1		   ,
	 0.80000001,
	 0.72949999,
	- 0.5472000,
	 0.41040000,
	 0.25	   ,
	 0.75	   ,
	 0.30000001,
	- 1.2000000,
	 0		   ,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0.625	   ,
	 0.30000001,
	 1.20000005,
	 0		   ,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0.625	   ,
	 0.30000001,
	 0.75	   ,
	 0.60000002,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0.75	   ,
	 0.30000001,
	- 0.75	   ,
	 0.60000002,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0.75	   ,
	 0		   ,
	- 1		   ,
	- 0.8000000,
	 0.55470001,
	 0		   ,
	- 0.8320999,
	 0.375	   ,
	 0.375	   ,
	 0		   ,
	 1		   ,
	- 0.8000000,
	 0.55470001,
	 0		   ,
	- 0.8320999,
	 0.625	   ,
	 0.375	   ,
	 0.30000001,
	 0.75	   ,
	- 0.6000000,
	 0.55470001,
	 0		   ,
	- 0.8320999,
	 0.625	   ,
	 0.5	   ,
	 0.30000001,
	- 0.75	   ,
	- 0.6000000,
	 0.55470001,
	 0		   ,
	- 0.8320999,
	 0.375	   ,
	 0.5	   ,
	 0.30000001,
	- 0.75	   ,
	- 0.6000000,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0.5	   ,
	 0.30000001,
	 0.75	   ,
	- 0.6000000,
	 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0.5	   ,
	 0		   ,
	- 1		   ,
	- 0.8000000,
	 0.72949999,
	- 0.5472000,
	- 0.4104000,
	 0.25	   ,
	 0.5	   ,
	 0.30000001,
	- 0.75	   ,
	- 0.6000000,
	 0.72949999,
	- 0.5472000,
	- 0.4104000,
	 0.375	   ,
	 0.5	   ,
	 0.30000001,
	- 1.2000000,
	 0		   ,
	 0.72949999,
	- 0.5472000,
	- 0.4104000,
	 0.375	   ,
	 0.625	   ,
	 0		   ,
	- 1.6000000,
	 0		   ,
	 0.72949999,
	- 0.5472000,
	- 0.4104000,
	 0.25	   ,
	 0.625	   ,
	- 0.3000000,
	- 0.75	   ,
	 0.60000002,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.375	   ,
	 0		   ,
	- 0.3000000,
	 0.75	   ,
	 0.60000002,
	- 1		   ,
	 0		   ,
	 0		   ,
	 0.625	   ,
	 0		   ,
	 0		   ,
	 1		   ,
	- 0.8000000,
	- 0.7294999,
	 0.54720002,
	- 0.4104000,
	 0.75	   ,
	 0.5	   ,
	- 0.3000000,
	 0.75	   ,
	- 0.6000000,
	- 0.7294999,
	 0.54720002,
	- 0.4104000,
	 0.875	   ,
	 0.5	   ,
	- 0.3000000,
	 1.20000005,
	 0		   ,
	- 0.7294999,
	 0.54720002,
	- 0.4104000,
	 0.875	   ,
	 0.625	   ,
	 0		   ,
	 1.60000002,
	 0		   ,
	- 0.7294999,
	 0.54720002,
	- 0.4104000,
	 0.75	   ,
	 0.625	   ,
	 0.30000001,
	 0.75	   ,
	- 0.6000000,
	 0.72949999,
	 0.54720002,
	- 0.4104000,
	 0.625	   ,
	 0.5	   ,
	 0		   ,
	 1		   ,
	- 0.8000000,
	 0.72949999,
	 0.54720002,
	- 0.4104000,
	 0.75	   ,
	 0.5	   ,
	 0		   ,
	 1.60000002,
	 0		   ,
	 0.72949999,
	 0.54720002,
	- 0.4104000,
	 0.75	   ,
	 0.625	   ,
	 0.30000001,
	 1.20000005,
	 0		   ,
	 0.72949999,
	 0.54720002,
	- 0.4104000,
	 0.625	   ,
	 0.625	   ,
	- 0.3000000,
	- 0.75	   ,
	- 0.6000000,
	- 0.7294999,
	- 0.5472000,
	- 0.4104000,
	 0.125	   ,
	 0.5	   ,
	 0		   ,
	- 1		   ,
	- 0.8000000,
	- 0.7294999,
	- 0.5472000,
	- 0.4104000,
	 0.25	   ,
	 0.5	   ,
	 0		   ,
	- 1.6000000,
	 0		   ,
	- 0.7294999,
	- 0.5472000,
	- 0.4104000,
	 0.25	   ,
	 0.625	   ,
	- 0.3000000,
	- 1.2000000,
	 0		   ,
	- 0.7294999,
	- 0.5472000,
	- 0.4104000,
	 0.125	   ,
	 0.625	   ,
	- 0.3000000,
	- 0.75	   ,
	- 0.6000000,
	- 0.5547000,
	 0		   ,
	- 0.8320999,
	 0.375	   ,
	 0.25	   ,
	- 0.3000000,
	 0.75	   ,
	- 0.6000000,
	- 0.5547000,
	 0		   ,
	- 0.8320999,
	 0.625	   ,
	 0.25	   ,
	 0		   ,
	 1		   ,
	- 0.8000000,
	- 0.5547000,
	 0		   ,
	- 0.8320999,
	 0.625	   ,
	 0.375	   ,
	 0		   ,
	- 1		   ,
	- 0.8000000,
	- 0.5547000,
	 0		   ,
	- 0.8320999,
	 0.375	   ,
	 0.375	   ,
	- 0.3000000,
	- 1.2000000,
	 0		   ,
	- 0.7294999,
	- 0.5472000,
	 0.41040000,
	 0.125	   ,
	 0.625	   ,
	 0		   ,
	- 1.6000000,
	 0		   ,
	- 0.7294999,
	- 0.5472000,
	 0.41040000,
	 0.25	   ,
	 0.625	   ,
	 0		   ,
	- 1		   ,
	 0.80000001,
	- 0.7294999,
	- 0.5472000,
	 0.41040000,
	 0.25	   ,
	 0.75	   ,
	- 0.3000000,
	- 0.75	   ,
	 0.60000002,
	- 0.7294999,
	- 0.5472000,
	 0.41040000,
	 0.125	   ,
	 0.75	   ,
	 0.30000001,
	- 0.75	   ,
	 0.60000002,
	 0.55470001,
	 0		   ,
	 0.83209997,
	 0.375	   ,
	 0.75	   ,
	 0.30000001,
	 0.75	   ,
	 0.60000002,
	 0.55470001,
	 0		   ,
	 0.83209997,
	 0.625	   ,
	 0.75	   ,
	 0		   ,
	 1		   ,
	 0.800	   ,
	 0.555	   ,
	 0.000	   ,
	 0.832	   ,
	 0.625	   ,
	 0.875	   ,
	 0.000	   ,
	- 1.000	   ,
	 0.80000001,
	 0.55470001,
	 0		   ,
	 0.83209997,
	 0.375	   ,
	 0.875	   ,
	 0.30000001,
	 1.20000005,
	 0		   ,
	 0.72949999,
	 0.54720002,
	 0.41040000,
	 0.625	   ,
	 0.625	   ,
	 0		   ,
	 1.60000002,
	 0		   ,
	 0.72949999,
	 0.54720002,
	 0.41040000,
	 0.75	   ,
	 0.625	   ,
	 0		   ,
	 1		   ,
	 0.80000001,
	 0.72949999,
	 0.54720002,
	 0.41040000,
	 0.75	   ,
	 0.75	   ,
	 0.30000001,
	 0.75	   ,
	 0.60000002,
	 0.72949999,
	 0.54720002,
	 0.41040000,
	 0.625	   ,
	 0.75
};

/// <summary>
/// A hardcoded array that contains indices of rupee vertices for each triangle in the mesh.
/// </summary>
const unsigned int rupeeIndices[] = {
0 ,
1 ,
2 ,
0 ,
2 ,
3 ,
4 ,
5 ,
6 ,
4 ,
6 ,
7 ,
8 ,
9 ,
10,
8 ,
10,
11,
12,
13,
14,
12,
14,
15,
16,
17,
18,
16,
18,
19,
20,
21,
22,
20,
22,
23,
24,
25,
17,
24,
17,
16,
26,
27,
28,
26,
28,
29,
30,
31,
9 ,
30,
9 ,
8 ,
32,
33,
34,
32,
34,
35,
36,
37,
38,
36,
38,
39,
40,
41,
42,
40,
42,
43,
44,
45,
46,
44,
46,
47,
48,
49,
50,
48,
50,
51,
52,
53,
54,
52,
54,
55,
56,
57,
58,
56,
58,
59
};

/// <summary>
/// A class that represents a hardcoded rupee object, which is also the only type of object in the scene that is semi-transparent.
/// </summary>
class Rupee
	: public StaticObject
{
private:
	static int s_numRupees;

	/// <summary>
	/// An unique identifier for the rupee object that is stored to a stencil buffer when rendering the rupee in order to identify it.
	/// </summary>
	int m_rupeeId;

	/// <summary>
	/// A flag that is used to determine if the rupee is spinning.
	/// </summary>
	bool m_spinning;
public:
	/// <summary>
	/// Default constructor for the Rupee class. Do not use.
	/// </summary>
	Rupee();

	/// <summary>
	/// The Rupee class constructor. Used to load the rupee from a JSON file.
	/// </summary>
	/// <param name="source">- JSON object that contains the rupee data.</param>
	Rupee(nlohmann::json source);

	/// <summary>
	/// A function that is called for each object in the scene for every frame. Each object updates all of its child objects. The function always calculates a global model matrix and propagates it to all child objects.
	/// </summary>
	/// <param name="deltaTime">- elapsed time from the last frame.</param>
	/// <param name="parentModelMatrix">- 4x4 matrix that describes the transformation of the parent object to world coordinates.</param>
	/// <param name="parentRotation">- quaternion that describes the rotation of the parent object relative to the world.</param>
	void Update(float deltaTime, const glm::mat4* parentModelMatrix, const glm::quat& parentRotation);

	/// <summary>
	/// Calls draw on all children of the given ObjectInstance. If the given object represents any geometry, it is drawn on the screen using an OpenGL draw call.
	/// </summary>
	void Draw();

	/// <summary>
	/// Generates all neccessary OpenGL objects. Pushes a pointer to the object into the <paramref name="transparentObjects"></paramref> list.
	/// </summary>
	/// <param name="transparentObjects">- vector with pointers to all objects that are marked as transparent.</param>
	/// <returns>false if any errors were encountered, true otherwise.</returns>
	bool GenObjects(std::vector<ObjectInstance *>& transparentObjects);

	/// <summary>
	/// Generates ImGui objects that will display properties of the object
	/// </summary>
	void ShowProperties() override;
};