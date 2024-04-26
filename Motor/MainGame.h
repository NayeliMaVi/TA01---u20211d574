#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include "Sprite.h"
#include "GLS_Program.h"
using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame {

private:
	Sprite sprite1;
	Sprite sprite2;
	int width;
	int height;
	SDL_Window* window;
	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;


public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();



};
