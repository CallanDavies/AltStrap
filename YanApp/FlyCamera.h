#pragma once
#include "Camera.h"
class FlyCamera : public Camera
{
public:

	virtual void Update(float a_fDeltaTime, GLFWwindow* a_GLWindow);

	void setSpeed(float a_fSpeed);

protected:
	// WASD motion Speed
	float m_fMoveSpeed = 10;
	// Mouse look Sensitivity
	float m_fMouseSpeed;
	// To rotate Around
	glm::vec3 m_fUp;

	// X Y of Mouse
	double m_dMouseX;
	double m_dMouseY;

	// Delta X Y of Mouse
	double m_dDeltaMouseX;
	double m_dDeltaMouseY;
};
