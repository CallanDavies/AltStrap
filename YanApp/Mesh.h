#pragma once
#include <glm\glm.hpp>
class Mesh
{
public:
	// Constructor sets all the variables to 0, 
	//which represents "uninitialised" in OpenGL
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}

	virtual ~Mesh();

	struct Vertex
	{
		glm::vec4 position;
		glm::vec4 normal;
		glm::vec2 texCoord;
	};

	void initialiseQuad();

	void initalise(unsigned int vertexCount, const Vertex* vertices,
		unsigned int indexCount = 0,
		unsigned int* indices = nullptr);

	virtual void draw();
protected:

	// Count of Triangles in mesh
	unsigned int triCount;
	//Vertex Array Object
	unsigned int vao;
	// Vertex Buffer Objects
	unsigned int vbo;
	// Index Buffer Object
	unsigned int ibo;
};

