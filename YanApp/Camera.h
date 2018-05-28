#pragma once
#include <glm\glm.hpp>
#include <glm\ext.hpp>
struct GLFWwindow;
class Camera
{
public:
	// Constucer
	Camera();
	// Deconstructor
	~Camera();

	// pure virtual update as each camera will have a unique update
	virtual void Update(float deltaTime, GLFWwindow* a_GLWindow) = 0;
	// Set a new perspective for the camera
	void SetPerspective(const float &a_fFOV, const float &a_fAspect, const float &a_fNear, const float a_fFar);
	// Set look from and to points 
	void SetLookAt(const glm::vec3 &a_v3From, const glm::vec3 &a_V3To, const glm::vec3 &a_V3Up);
	// Move the camera to this position
	void SetPosition(const glm::vec3 &a_V3Position);
	// Camera's World transform
	glm::mat4 GetWorldTransform() const
	{
		return m_worldTransform;
	}
	// Camera's view transform
	glm::mat4 GetViewTransform() const
	{
		return m_viewTransform;
	}
	// Camera's projection transform
	glm::mat4 GetProjectionTransform() const
	{
		return m_projectionTransform;
	}
	// Get a precalculated Projection x View Transform
	glm::mat4 GetProjectionViewTransform() const
	{
		return m_projectionViewTransform;
	}
	
protected:
	// Camera Position and rotation
	glm::mat4  m_worldTransform;
	// Inverse world transform
	glm::mat4 m_viewTransform;
	// Projection matrix info
	glm::mat4 m_projectionTransform;
	// Projection x View transformations
	glm::mat4 m_projectionViewTransform;

	// Update whever the projection of view changed
	void UpdateProjectionViewTransform();

};

