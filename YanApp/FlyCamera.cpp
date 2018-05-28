#include "FlyCamera.h"
#include <glfw3.h>

void FlyCamera::Update(float a_fDeltaTime, GLFWwindow* a_GLWindow)
{
	// Calculate delta XY of mouse
	glfwGetCursorPos(a_GLWindow, &m_dMouseX, &m_dMouseY);
	// Radians to degrees
	m_dDeltaMouseX = (400 - m_dMouseX) * 0.0174533;
	m_dDeltaMouseY = (300 - m_dMouseY) * 0.0174533;

	// Keep mouse locked to screen
	glfwSetCursorPos(a_GLWindow, 400, 300);

	// Calculate relative world up
	glm::vec4 up = glm::inverse(m_worldTransform) * glm::vec4(0, 1, 0, 0);
	glm::mat4 rotMat(1.0f);
	// Rotate around world up
	rotMat = glm::rotate((float)-m_dDeltaMouseX * a_fDeltaTime, glm::vec3(up[0], up[1], up[2]));
	m_viewTransform = rotMat * m_viewTransform;
	// Rotate up down
	rotMat = glm::rotate((float)-m_dDeltaMouseY * a_fDeltaTime, glm::vec3(1, 0, 0));
	m_viewTransform = rotMat * m_viewTransform;
	// Update World Transform
	m_worldTransform = glm::inverse(m_viewTransform);

	//Keyboard Input
	if (glfwGetKey(a_GLWindow, GLFW_KEY_W))
	{
		m_worldTransform[3] += m_worldTransform[2] * a_fDeltaTime * -m_fMoveSpeed;
	}
	if (glfwGetKey(a_GLWindow, GLFW_KEY_S))
	{
		m_worldTransform[3] += m_worldTransform[2] * a_fDeltaTime * m_fMoveSpeed;
	}
	if (glfwGetKey(a_GLWindow, GLFW_KEY_A))
	{
		m_worldTransform[3] += m_worldTransform[0] * a_fDeltaTime * -m_fMoveSpeed;
	}
	if (glfwGetKey(a_GLWindow, GLFW_KEY_D))
	{
		m_worldTransform[3] += m_worldTransform[0] * a_fDeltaTime * m_fMoveSpeed;
	}

	m_worldTransform[3][3] = 1.0f;
	m_viewTransform = glm::inverse(m_worldTransform);

	UpdateProjectionViewTransform();

}

void FlyCamera::setSpeed(float a_fSpeed)
{
	m_fMoveSpeed = a_fSpeed;
}
