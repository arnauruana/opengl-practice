#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include "Quad.h"
#include "ShaderProgram.h"
#include "Text.h"
#include "TexturedQuad.h"

#include <glm/glm.hpp>


typedef unsigned int uint;


/*
	Contains all the entities of our game
	Updates and renders all of them
*/
class Scene
{
public:
	static const uint CAMERA_WIDTH  = 640;
	static const uint CAMERA_HEIGHT = 480;

	bool jump;
	bool renderS;
	bool textP;

public:
	Scene();
	~Scene();

	void init();
	void update(int time);
	void render();

private:
	void initShaders();

private:
	float prev;
	float time;

	glm::mat4 projection;

	Quad* quad;

	ShaderProgram simpleShader, textureShader;

	Texture texs[5];
	TexturedQuad* texQuad[4];

	Text text;
};


#endif // _SCENE_INCLUDE