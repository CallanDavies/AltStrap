#include "FlyCamera.h"

void FlyCamera::Update(float a_fDeltaTime, GLFWwindow* a_GLWindow)
{
	//// Calculate delta XY of mouse
	//glfwGetCursorPos(a_GLWindow, &m_dMouseX, &m_dMouseY);
	//// Radians to degrees
	//m_dDeltaMouseX = (400 - m_dMouseX) * 0.0174533;
	//m_dDeltaMouseY = (300 - m_dMouseY) * 0.0174533;

	//// Keep mouse locked to screen
	//glfwSetCursorPos(a_GLWindow, 400, 300);

	//// Calculate relative world up
	//glm::vec4 up = glm::inverse(m_worldTransform) * glm::vec4(0, 1, 0, 0);
	//glm::mat4 rotMat(1.0f);
	//// Rotate around world up
	//rotMat = glm::rotate((float)-m_dDeltaMouseX * a_fDeltaTime, glm::vec3(up[0], up[1], up[2]));
	//m_viewTransform
}