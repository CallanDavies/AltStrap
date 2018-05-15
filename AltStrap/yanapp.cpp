#include "yanapp.h"

yan::application::application()
{
	m_window = nullptr;
	m_gameOver = false;
}

void yan::application::run(const char * title, int width, int height)
{
	if (createWindow(title, width, height) && startup())
		{

		time m_startTime = m_clock.now();
		time m_currentTime = m_clock.now();
		time m_previousTime = m_clock.now();
		auto duration = m_currentTime - m_previousTime;
		float deltaTime = duration.count() * NANO_TO_SECONDS;

		while (!m_gameOver && glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
		{
			//update delta time
			m_previousTime = m_currentTime;
			m_currentTime = m_clock.now();
			auto duration = m_currentTime - m_previousTime;
			double deltaTime = duration.count() * NANO_TO_SECONDS;

			update(float(deltaTime));

			draw();

			//should the game exit?
			m_gameOver = m_gameOver || glfwWindowShouldClose(m_window) == GLFW_TRUE;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
        }

	// Cleanup
	shutdown();
	destroyWindow();
}

bool yan::application::createWindow(const char * title, int width, int height)
{
	// Check if we can hook into the GPU
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	// Create the window
	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	// Check if window worked
	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	// Bring to front
	glfwMakeContextCurrent(m_window);

	// ..before loading interface functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return false;

	}

	// glClearColour
	glClearColor(0.5f, 0.25f, 0.25f, 1);
	// Enable Depth
	glEnable(GL_DEPTH_TEST);

	// AIE Gizmos - TODO: Better Numbers
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	// Camera: position and direction
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	// FOV setter
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);

	return true;
}

void yan::application::destroyWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
