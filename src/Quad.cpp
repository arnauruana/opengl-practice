#include <GL/glew.h>
#include <GL/gl.h>

#include "Quad.h"


Quad::Quad(float x, float y, float width, float height, ShaderProgram& program)
{
	float vertices[12] =
	{
		x,
		y,
		x + width,
		y,
		x + width,
		y + height,
		x,
		y,
		x + width,
		y + height,
		x,
		y + height
	};

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);
	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);

	posLocation = program.bindVertexAttribute("position", 2, 0, 0);
}

Quad* Quad::createQuad(float x, float y, float width, float height, ShaderProgram& program)
{
	Quad* quad = new Quad(x, y, width, height, program);
	return quad;
}


void Quad::render() const
{
	glBindVertexArray(this->vao);
	glEnableVertexAttribArray(this->posLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Quad::free()
{
	glDeleteBuffers(1, &this->vbo);
}
