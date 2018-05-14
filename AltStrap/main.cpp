#include <iostream>
// Maths
#include <glm.hpp>
#include <ext.hpp> // Maths Extension

#include "../dependencies/glCore/gl_core_4_5.h"
#include <glfw3.h>

#include "Gizmos.h"

int main()
{

	// If we can hook into the GPU
	if (glfwInit() == false)
	{
		// -1 is a failure code.
		return -1;
	}

	// Bonus monitor counters
	GLFWmonitor** screens;
	int count = 0;
	screens = glfwGetMonitors(&count);
	std::cout << count << std::endl;

	// Make a window with OpenGL render
	GLFWwindow* window =
                        //Width, Height
		glfwCreateWindow(1280, 720, 
			            // Window Name
	                    "AltStrap",
			            //Screen Pointer
			            nullptr, nullptr);

	// Check if window worked
	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}
	// Bring to front
	glfwMakeContextCurrent(window);

	// ..before loading interface functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Open GL version
	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	// glClearColour
	glClearColor(0.5f, 0.25f, 0.25f, 1);
	// Enable Depth
	glEnable(GL_DEPTH_TEST);

	// AIE Gizmos - TODO: Better Numbers
	aie::Gizmos::create(10000,10000,10000,10000);

	// Camera: position and direction
	glm::mat4 view = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	// FOV setter
	glm::mat4 projection = glm::perspective(glm::pi<float>() * 0.25f,
		16 / 9.f, 0.1f, 1000.f);


	// While...
	while (glfwWindowShouldClose(window) == false &&
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		// Clearing Buffer - colour and depth checks.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// our game logic and update code goes here!
		// so does our render code!

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

		// Move all objects into somewhere the camera can see it.
		aie::Gizmos::draw(projection * view);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//pause before terminate
	//std::cin.get();

	// the rest of our code goes here!
	glfwDestroyWindow(window);

	// Clean up window and gpu linkage
	aie::Gizmos::destroy();
	glfwTerminate();

	return 0;
}