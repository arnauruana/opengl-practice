#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.hh"


/*
	Singleton that represents our whole application.
*/
class Game
{
public:
	static const uint DEFAULT_WINDOW_WIDTH  = 640;
	static const uint DEFAULT_WINDOW_HEIGHT = 480;

	static const uint FPS = 60;

public:
	Game() {}

	static Game& instance()
	{
		static Game game;
		return game;
	}

	void init();
	bool update(int time);
	void render();

	bool getKey(int keyId) const;
	bool getSpecialKey(int keyId) const;

	void keyPressed(int keyId);
	void keyReleased(int keyId);
	void specialKeyPressed(int keyId);
	void specialKeyReleased(int keyId);

	void mousePressed(int buttonId);
	void mouseReleased(int buttonId);
	void mouseMoved(int posX, int posY);

private:
	void toggleFullScreen();
	void enableFullScreen();
	void disableFullScreen();

	void saveWindowContext();
	void restoreWindowContext();

private:
	bool bPlay;

	bool key[256];
	bool skey[256];

	bool mouseA;

	bool windowF;
	uint windowH;
	uint windowW;
	uint windowX;
	uint windowY;

	bool soundA;

	Scene scene;
};


#endif // _GAME_INCLUDE
