#pragma once
#include <SDL/SDL.h>
#include<GL/eglew.h>
#include <iostream>
#include<vector>
#include <cmath>
#include<memory>
#include "Sprite.h"
#include "GLS_Program.h"
#include "Window.h"

using namespace std;

enum class GameState {

	PLAY, EXIT

};

class MainGame {

private:
	//Sprite sprite1;
	//Sprite sprite2;
	Sprite sprite;

	int width;
	int height;

	//SDL_Window* window;
	Window* window;

	void init();
	void processInput();
	GLS_Program program;
	void initShaders();
	float time = 0;
	int cont = 1;

public:
	MainGame();
	~MainGame();
	GameState gameState;
	void run();
	void draw();
	void update();



};
