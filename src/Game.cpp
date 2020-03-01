#include "Game.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>


void Game::init()
{
	//PlaySound(TEXT("music/mario.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	this->bPlay	  = true;
	this->mouseA  = false;
	this->windowF = false;
	this->soundA  = true;

	this->scene.init();
}

bool Game::update(int deltaTime)
{
	this->scene.update(deltaTime);

	return this->bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->scene.render();
}


bool Game::getKey(int key) const
{
	return this->key[key];
}

bool Game::getSpecialKey(int key) const
{
	return this->skey[key];
}


void Game::keyPressed(int key)
{
	this->key[key] = true;

	switch (key)
	{
		case '0':
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			break;
		}
		case '1':
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			break;
		}
		case '2':
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			break;
		}
		case '3':
		{
			glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
			break;
		}
		case '4':
		{
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			break;
		}
		case '5':
		{
			glClearColor(0.525f, 0.525f, 0.525f, 1.0f);
			break;
		}
		case '6':
		{
			glClearColor(0.65f, 0.65f, 0.65f, 1.0f);
			break;
		}
		case '7':
		{
			glClearColor(0.775f, 0.775f, 0.775f, 1.0f);
			break;
		}
		case '8':
		{
			glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
			break;
		}
		case '9':
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
		case 'f':
		{
			this->toggleFullScreen();
			break;
		}
		case 'c':
		{
			this->mouseA = not this->mouseA;
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			break;
		}
		case 't':
		{
			this->scene.textP = not this->scene.textP;
			break;
		}
		case 'm':
		{
			this->soundA = not this->soundA;
			if (not this->soundA)
			{
				//PlaySound(NULL, NULL, 0);
			}
			else
			{
				//PlaySound(TEXT("music/mario.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
			}
			break;
		}
		case ' ':
		{
			this->scene.jump = true;
			break;
		}
		case 27: // escape
		{
			if (this->windowF)
			{
				this->disableFullScreen();
			}
			else
			{
				this->bPlay = false;
			}
			break;
		}
		default:
		{
		}
	}
}

void Game::keyReleased(int key)
{
	this->key[key] = false;

	switch (key)
	{
		case 'r':
		{
			this->scene.renderS = not this->scene.renderS;
			break;
		}
		case ' ':
		{
			this->scene.jump = false;
			break;
		}
		default:
		{
		}
	}
}

void Game::specialKeyPressed(int key)
{
	this->skey[key] = true;

	switch (key)
	{
		case GLUT_KEY_F11:
		{
			this->toggleFullScreen();
			break;
		}
		default:
		{
		}
	}
}

void Game::specialKeyReleased(int key)
{
	this->skey[key] = false;
}


void Game::mousePressed(int button)
{
}

void Game::mouseReleased(int button)
{
}

void Game::mouseMoved(int x, int y)
{
	if (not this->mouseA) return;

	int width  = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	if (x < width / 2)
	{
		if (y < height / 2)
		{
			glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red
		}
		else
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // white
		}
	}
	else
	{
		if (y < height / 2)
		{
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // green
		}
		else
		{
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // blue
		}
	}
}


void Game::toggleFullScreen()
{
	if (not this->windowF)
	{
		this->enableFullScreen();
	}
	else
	{
		this->disableFullScreen();
	}
}

void Game::enableFullScreen()
{
	this->saveWindowContext();
	this->windowF = true;

	glutFullScreen();
}

void Game::disableFullScreen()
{
	this->restoreWindowContext();
	this->windowF = false;
}


void Game::saveWindowContext()
{
	this->windowX = glutGet(GLUT_WINDOW_X);
	this->windowY = glutGet(GLUT_WINDOW_Y);

	this->windowW = glutGet(GLUT_WINDOW_WIDTH);
	this->windowH = glutGet(GLUT_WINDOW_HEIGHT);
}

void Game::restoreWindowContext()
{
	glutPositionWindow(this->windowX, this->windowY);
	glutReshapeWindow(this->windowW, this->windowH);
}
