#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetPerspective(const float & a_fFOV, const float & a_fAspect, const float & a_fNear, const float a_fFar)
{
	m_projectionTransform = glm::perspective(a_fFOV, a_fAspect, a_fNear, a_fFar);
}

void Camera::SetLookAt(const glm::vec3 & a_v3From, const glm::vec3 & a_V3To, const glm::vec3 & a_V3Up)
{
	m_viewTransform = glm::lookAt(a_v3From, a_V3To, a_V3Up);
	m_worldTransform = glm::inverse(m_viewTransform);

	UpdateProjectionViewTransform();
}

void Camera::SetPosition(const glm::vec3 & a_V3Position)
{
	m_worldTransform[3] = glm::vec4(a_V3Position.x,a_V3Position.y,a_V3Position.z,1);
	m_viewTransform = glm::inverse(m_worldTransform);

	UpdateProjectionViewTransform();
}

void Camera::UpdateProjectionViewTransform()
{
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}
