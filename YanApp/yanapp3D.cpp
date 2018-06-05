#include "yanapp3D.h"

application3D::application3D() : application()
{

}

application3D::~application3D()
{

}

bool application3D::startup()
{
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1 , 0 };
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	// Parent Object
	parentMatrix = glm::mat4(1);

	// Child Object
	localMatrix = glm::mat4(1);
	globalMatrix = glm::mat4(1);

	// Camera: position and direction
	m_pCamera = new FlyCamera();
	m_pCamera->SetLookAt(glm::vec3(50), glm::vec3(0), glm::vec3(0, 1, 0));
	m_pCamera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);
	m_pCamera->SetPosition(glm::vec3(0, 10, 0));

	/*m_shader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/simple.frag");

	m_texturedshader.loadShader(aie::eShaderStage::VERTEX,
		"../shaders/textured.vert");
	m_texturedshader.loadShader(aie::eShaderStage::FRAGMENT,
		"../shaders/textured.frag");*/

	/*if (m_shader.link() == false)
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	if (m_texturedshader.link() == false)
	{
		printf("Shader Error: %s\n", m_texturedshader.getLastError());
		return false;
	}

	if (m_gridTexture.load("../textures/numbered_grid.tga") == false)
	{
		printf("Failed to load Texture!\n");
		return false;
	}*/

	m_phongShader.loadShader(aie::eShaderStage::VERTEX,
	"../shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT,
	"../shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	// make the quad 1 units wide
	m_quadTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
	// define 6 vertices for 2 triangles
	Mesh::Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	vertices[0].texCoord = { 0,1 };
	vertices[1].texCoord = { 1,1 };
	vertices[2].texCoord = { 0,0 };

	vertices[3].texCoord = { 0,0 };
	vertices[4].texCoord = { 1,1 };
	vertices[5].texCoord = { 1,0 };

	m_quadMesh.initalise(6, vertices);

	if (m_bunnyMesh.load("../models/soulspear.obj") == false)
	{
		printf("Bunny Mesh Error!\n");
		return false;
	}

	m_bunnyTransform =
	{
		0.5f,0,0,0,
		0,0.5f,0,0,
		0,0,0.5f,0,
		0,0,0,1
	};

	// Hide the Cursor on window
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	aie::Texture texture1;
	texture1.load("mytexture.png");

	return true;
}

void application3D::shutdown()
{
	aie::Gizmos::destroy();
	delete m_pCamera;
}

void application3D::update(float deltaTime)
{
	float time = glfwGetTime();
	
	m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));

	m_pCamera->Update(deltaTime,m_window);
}

void application3D::draw()
{
	// bind phong shader
	m_phongShader.bind();

	// bind light
	m_phongShader.bindUniform("Ia", m_ambientLight);
	m_phongShader.bindUniform("Id", m_light.diffuse);
	m_phongShader.bindUniform("Is", m_light.specular);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	// bind transform of Phong shader
	auto pvm = m_pCamera->GetProjectionViewTransform() * m_quadTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// bind transforms for lighting
	m_phongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_quadTransform)));

	// bing transform for camera position
	m_phongShader.bindUniform("cameraPosition", m_pCamera->GetPosition());

	// draw quad
	//m_quadMesh.draw();

	// draw object
	m_bunnyMesh.draw();
}
