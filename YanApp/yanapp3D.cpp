#include "yanapp3D.h"

application3D::application3D() : application()
{

}

application3D::~application3D()
{

}

bool application3D::startup()
{
	// AIE Gizmos - TODO: Better Numbers
	//aie::Gizmos::create(10000, 10000, 10000, 10000);
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
	aie::Gizmos::clear();
	// Adds the axis widget to the scene
	aie::Gizmos::addTransform(glm::mat4(1));
	// Vec4 value for colours.
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);
	// Building a 3D Grid
	for (int i = 0; i < 21; ++i) {
		aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);
		aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// create rotation matrix
	glm::mat4 rot(1);
	rot = glm::rotate(deltaTime, glm::vec3(0, 1, 0));
	// Apply rotation to Parent
	// Parent Orbits centre
	parentMatrix = rot * parentMatrix;
	aie::Gizmos::addSphere(glm::vec3(0), 1, 2, 2, white, &parentMatrix);
	// Parent Spins
	rot = glm::rotate(deltaTime * 3, glm::vec3(0, 1, 0));
	parentMatrix = parentMatrix * rot;

	//Rotate Child around Parent...
	rot = glm::rotate(deltaTime * -2, glm::vec3(0, 1, 0));
	localMatrix = rot * localMatrix;

	//... once child Syncs. with parent
	globalMatrix = parentMatrix * localMatrix;
	aie::Gizmos::addSphere(glm::vec3(0), 0.5f, 20, 20, black, &globalMatrix);

	m_pCamera->Update(deltaTime,m_window);
}

void application3D::draw()
{
	// Move all objects into somewhere the camera can see it.
	aie::Gizmos::draw(m_pCamera->GetProjectionViewTransform());

}
