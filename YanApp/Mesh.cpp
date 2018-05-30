#include "Mesh.h"
#include <glCore\gl_core_4_5.h>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initialiseQuad()
{
	// check that the mesh is not itialized already
	assert(vao == 0);

	// Generate Buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	//bind vertex array AKA a mesh wrapper
	glBindVertexArray(vao);
	
	// bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// define 6 vertices for 2 triangles
	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { 0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };

	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = { 0.5f, 0, 0.5f, 1 };
	vertices[5].position = { 0.5f, 0, -0.5f, 1 };

	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//quad has 2 triangles
	triCount = 2;

	// MORE TO GO HERE
}

void Mesh::initalise(unsigned int vertexCount, const Vertex * vertices, unsigned int indexCount /* = 0*/, unsigned int * indices /* = nullptr*/)
{
	assert(vao == 0);

	// generate buffers
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	// bind vertex arrays aka a mesh wrapper
	glBindVertexArray(vao);

	//bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	


	// fill vertex buffer
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	// enable first element as position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	// enable third element as texture
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);

	// bind indices if there are any
	if (indexCount != 0)
	{
		glGenBuffers(1, &ibo);

		// bind vertex buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// find vertex buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		triCount = indexCount / 3;
	}
	else
	{
		triCount = vertexCount / 3;
	}

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::draw()
{
	glBindVertexArray(vao);
	//using indices or just vertices?
	if (ibo != 0)
	{
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
	}
}
