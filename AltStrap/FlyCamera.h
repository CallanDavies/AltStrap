#pragma once
#include "Camera.h"
#include <ext.hpp> // Maths Extension
class FlyCamera : public Camera
{
	virtual void Update(float a_fDeltaTime, GLFWwindow* a_GLWindow);
};
