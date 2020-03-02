#ifndef _QUAD_INCLUDE
#define _QUAD_INCLUDE


#include "ShaderProgram.hh"


/*
	Given a point (x, y) and a size (width, height) in pixels Quad creates
	a VBO with two triangles. Vertices in the VBO have only a position
	attribute (no colors or texture coordinates)
*/
class Quad
{
public:
	Quad(float posX, float posY, float width, float height, ShaderProgram& shadProg);

	static Quad* createQuad(float posX, float posY, float width, float height, ShaderProgram& shadProg);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;

	GLint posLocation;
};


#endif // _QUAD_INCLUDE
