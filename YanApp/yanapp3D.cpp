#include "yanapp3D.h"

application3D::application3D() : application()
{

}

application3D::~application3D()
{

}

bool application3D::startup()
{
	// Setup for first light
	m_light.diffuse = { 1, 1, 0 };
	m_light.specular = { 1, 1 , 0 };
	// ambient Light setup
	m_ambientLight = { 0.25f, 0.25f, 0.25f };

	// Setup for second light
	m_secondLight.diffuse = { 1, 0, 0 };
	m_secondLight.specular = { 1, 0 , 0 };

	// Camera: position and direction
	m_pCamera = new FlyCamera();
	m_pCamera->SetLookAt(glm::vec3(50), glm::vec3(0), glm::vec3(0, 1, 0));
	m_pCamera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.f);
	m_pCamera->SetPosition(glm::vec3(6.25, 6.25, 6.25));
	
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX,
	"../shaders/normalmap.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT,
	"../shaders/normalmap.frag");

	if (m_texturedShader.link() == false)
	{
		printf("Shader Error: %s\n", m_texturedShader.getLastError());
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

	if (m_SSpearMesh.load("../models/soulspear.obj", true, true) == false)
	{
		printf("Soul Spear Mesh Error!\n");
		return false;
	}

	if (m_RockMesh.load("../models/Rock.obj", true, true) == false)
	{
		printf("Rock Mesh Error!\n");
		return false;
	}

	m_SSpearTransform =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	m_RockTransform =
	{
		0.4f,0,0,0,
		0,0.4f,0,0,
		0,0,0.4f,0,
		2,0,0,1
	};

	// Hide the Cursor on window
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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

	m_secondLight.direction = glm::normalize(glm::vec3(glm::cos(time * 0.5f), glm::sin(time * 0.5f), 0));

	m_pCamera->Update(deltaTime,m_window);
}

void application3D::draw()
{
	// bind shader
	m_texturedShader.bind();

	// bing transform for camera position
	m_texturedShader.bindUniform("cameraPosition", m_pCamera->GetPosition());

	// bind light
	m_texturedShader.bindUniform("Ia", m_ambientLight);
	m_texturedShader.bindUniform("Id", m_light.diffuse);
	m_texturedShader.bindUniform("Is", m_light.specular);
	m_texturedShader.bindUniform("LightDirection", m_light.direction);

	m_texturedShader.bindUniform("Id2", m_secondLight.diffuse);
	m_texturedShader.bindUniform("Is2", m_secondLight.specular);
	m_texturedShader.bindUniform("LightDirection2", m_secondLight.direction);

	// bind transform of shader
	auto pvm = m_pCamera->GetProjectionViewTransform() * m_SSpearTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	// bind transforms for the normal
	m_texturedShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_SSpearTransform)));
	m_SSpearMesh.draw();

	// bind transform of shader
	pvm = m_pCamera->GetProjectionViewTransform() * m_RockTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);
	// bind transforms for the normal
	m_texturedShader.bindUniform("NormalMatrix", m_RockTransform);
	m_RockMesh.draw();
}
