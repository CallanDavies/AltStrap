#pragma once
#include <iostream>
#include <chrono>
// Maths
#include <glm.hpp>
#include <ext.hpp> // Maths Extension

#include "../dependencies/glCore/gl_core_4_5.h"
#include <glfw3.h>

#include "Gizmos.h"



namespace yan
{
	using clock = std::chrono::high_resolution_clock;
	using time = std::chrono::time_point<clock>;

	/* TIME, CLOCK, AND DURATION ALIASING */
	using ullong = unsigned long long;
	using nanoseconds = std::chrono::nanoseconds;

	// Expected use: seconds = nanoseconds * NANO_TO_SECONDS
	static const double NANO_TO_SECONDS = 0.000000001;
	// Expected use: nanodesconds = seconds * NANO_IN_SECONDS
	static const ullong NANO_IN_SECONDS = 10000000000ULL;


	class application
	{
	public:
		
		application();
		void run(const char* title, int width, int height);

		virtual bool startup() = 0;
		virtual void shutdown() = 0;
		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

	protected:
		virtual bool createWindow(const char* title, int width, int height);
		virtual void destroyWindow();

		GLFWwindow* m_window;
		clock m_clock;
		//if set to false, the main game loop will exit
		bool m_gameOver;

	};
} 