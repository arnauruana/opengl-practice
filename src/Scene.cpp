#include "Scene.h"

#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

#include <GL/glut.h>


Scene::Scene()
{
	this->quad = NULL;

	this->jump = false;
	this->renderS = false;
	this->textP = true;

	this->prev = 0.f;
}

Scene::~Scene()
{
	if (quad != NULL)
		delete this->quad;

	for (int i = 0; i < 3; i++)
		if (texQuad[i] != NULL)
			delete texQuad[i];
}


void Scene::init()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };

	initShaders();

	quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, simpleShader);

	// SKY
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, textureShader);

	// BRICKS
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(6.f, 1.4f);
	texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, textureShader);

	// MARIO
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, textureShader);

	// CLOUD
	texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(1.f, 1.f);
	texQuad[3] = TexturedQuad::createTexturedQuad(geom, texCoords, textureShader);

	texs[0].loadFromFile("images/sky.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[1].loadFromFile("images/bricks.jpg", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[2].loadFromFile("images/mario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[3].loadFromFile("images/jump.png", TEXTURE_PIXEL_FORMAT_RGBA);
	texs[4].loadFromFile("images/cloud.png", TEXTURE_PIXEL_FORMAT_RGBA);

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	time = 0.0f;

	// Select which font you want to use
	if (not text.init("fonts/OpenSans-Bold.ttf"))
	{
		cout << "Could not load font!!!" << endl;
	}
}

void Scene::update(int deltaTime)
{
	if (not this->renderS) return;

	this->time += deltaTime;
}

void Scene::render()
{
	if (not this->renderS) return;

	GLfloat bounce = sin(time / 1000.f) * 285;
	GLfloat jumped = jump ? -30.f : 0.f;

	GLboolean right = bounce > this->prev;
	this->prev = bounce;

	GLfloat bounceC1 = cos(time / 20000.f) * 260;
	GLfloat bounceC2 = cos(time / 15000.f) * 240;

	textureShader.use();
	textureShader.setUniformMatrix4f("projection", projection);
	textureShader.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	glm::mat4 modelview;

	// SKY
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(-64.f, -64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(6, 5, 0));
	textureShader.setUniformMatrix4f("modelview", modelview);
	texQuad[0]->render(texs[0]);

	// CLOUD 1
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(253.f, -10.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-bounceC1, 0.f, 0.f));
	textureShader.setUniformMatrix4f("modelview", modelview);
	texQuad[3]->render(texs[4]);

	// CLOUD 2
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(253.f, 40.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(bounceC2, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(1.5, 1.5, 0));
	modelview = glm::rotate(modelview, 3.14159265f, glm::vec3(0.f, 1.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	textureShader.setUniformMatrix4f("modelview", modelview);
	texQuad[3]->render(texs[4]);

	// BRIKCS
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-10.f, 300.f, 0.f));
	modelview = glm::scale(modelview, glm::vec3(6.1, 1.4, 0));
	textureShader.setUniformMatrix4f("modelview", modelview);
	texQuad[1]->render(texs[1]);

	// MARIO
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(253.f, 215.f, 0.f));
	modelview = glm::translate(modelview, glm::vec3(bounce, jumped, 0.f));
	modelview = glm::translate(modelview, glm::vec3(64.f, 64.f, 0.f));
	if (not right)
	{
		modelview = glm::rotate(modelview, 3.14159265f, glm::vec3(0.f, 1.f, 0.f));
	}
	modelview = glm::scale(modelview, glm::vec3(0.5, 0.5, 0));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	textureShader.setUniformMatrix4f("modelview", modelview);
	texQuad[2]->render(this->jump ? texs[3] : texs[2]);

	// AUTHOR
	if (this->textP)
	{
		text.render("Arnau Ruana - VJ", glm::vec2(10, glutGet(GLUT_WINDOW_HEIGHT) - 10), 32, glm::vec4(1, 1, 1, 1));
	}
}


void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleShader.init();
	simpleShader.addShader(vShader);
	simpleShader.addShader(fShader);
	simpleShader.link();
	if (!simpleShader.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleShader.log() << endl << endl;
	}
	simpleShader.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	textureShader.init();
	textureShader.addShader(vShader);
	textureShader.addShader(fShader);
	textureShader.link();
	if (!textureShader.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << textureShader.log() << endl << endl;
	}
	textureShader.bindFragmentOutput("outColor");
}
