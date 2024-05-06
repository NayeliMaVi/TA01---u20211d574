#include "MainGame.h"
#include "Sprite.h"

MainGame::MainGame()
{
	window = NULL;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;

}

void MainGame::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	window = new Window();
	window->create("Waos", width, height, 0);

	initShaders();

	//window = SDL_CreateWindow("waos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	//SDL_GLContext glContext = SDL_GL_CreateContext(window);
	//GLenum error = glewInit();

	//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//glClearColor(184.0f / 255.0f, 213.0f / 255.0f, 238.0f / 255.0f, 1.0f);

}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	//sprite1.init(-1,-1,1,1);
	//sprite2.init(0, 0, 1, 1);
	sprite.init(-1, -1, 1, 1, "images/xiao.png");
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.05;
	/*
	sprite1.draw();
	if(time>4)
	sprite2.draw();
	*/
	sprite.draw();
	program.unuse();
	window->swapWindow();



}

void MainGame::update()
{
	
	int temp = 30;
	int index = 0;
	

	while (gameState != GameState::EXIT) {
		draw();
		 temp--;

		 if (temp == 0) {

			 switch (index) {
				 case 0:
					 sprite.init(0, -1, 1, 1, "images/troste.png"); // Esquina inferior der
					 
					 break;
				 case 1:
					 sprite.init(0, 0, 1, 1, "images/xiao.png"); // Esquina superior der
					
					 break;
				 case 2:
					 sprite.init(-1, 0, 1, 1, "images/troste.png"); // Esquina superior izq
					 
					 break;
				 case 3:
					 sprite.init(-1, -1, 1, 1, "images/xiao.png"); // Esquina inf izquierda
					
					 break;
				 case 4:
					 sprite.init(0.5, 0.5, -1, -1, "images/scara.png"); // medio

					 break;
			 }

			 if(index<5)
			 index = (index + 1);
			 else
			 index = 0;

			 temp = 60;
		 }

		processInput();
	}
}



void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			cout << " Posicion en X " << event.motion.x
				<< " Posicion en Y " << event.motion.y << endl;
			break;
		}
	}
}

void MainGame::initShaders()
{
	program.compileShaders("Shaders/colorShaderVert.txt", "Shaders/colorShaderFrag.txt");
	program.addAtribute("vertexPoistion");
	program.addAtribute("vertexColor");
	program.addAtribute("vertexUV");
	program.linkShader();

}
