#pragma once

#include "yanapp.h"

class application3D : public yan::application
{
public:
	application3D();
	virtual ~application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	// Parent Object
	glm::mat4 parentMatrix;

	// Child Object
	glm::mat4 localMatrix;
	glm::mat4 globalMatrix;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
};
