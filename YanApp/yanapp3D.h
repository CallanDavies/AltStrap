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

	//Shaders
	aie::ShaderProgram m_shader;
	// Textured Shader
	aie::ShaderProgram m_texturedshader;

	Mesh m_quadMesh;
	glm::mat4 m_quadTransform;

	//Bunny values
	aie::OBJMesh m_bunnyMesh;
	glm::mat4 m_bunnyTransform;
};
