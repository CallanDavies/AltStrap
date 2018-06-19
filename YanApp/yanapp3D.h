#pragma once

#include "yanapp.h"
#include "FlyCamera.h"
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

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

	// Texture for the grid
	aie::Texture m_gridTexture;

	// Camera
	FlyCamera* m_pCamera;

	// Phong Shader
	aie::ShaderProgram m_texturedShader;

	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	//Spear values
	aie::OBJMesh m_SSpearMesh;
	glm::mat4 m_SSpearTransform;

	// Rock values
	aie::OBJMesh m_RockMesh;
	glm::mat4 m_RockTransform;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
	Light m_light;
	Light m_secondLight;
	glm::vec3 m_ambientLight;
};
