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
	window = SDL_CreateWindow("waos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	//es valida si hubo un error
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		//falta validar el estado del glew
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glClearColor(184.0f / 255.0f, 213.0f / 255.0f, 238.0f / 255.0f, 1.0f);
	initShaders();

}

MainGame::~MainGame()
{


}

void MainGame::run()
{
	init();
	sprite1.init(-1,-1,1,1);
	sprite2.init(0, 0, 1, 1);
	update();
}

void MainGame::draw()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	GLuint timeLocation = program.getUniformLocation("time");
	glUniform1f(timeLocation, time);
	time += 0.02;
	sprite1.draw();
	if(time>4)
	sprite2.draw();
	program.unuse();
	SDL_GL_SwapWindow(window);



}

void MainGame::update()
{
    int temp = 60; 
    int index = 0; 

    while (gameState != GameState::EXIT) {
        draw(); 
        temp--; 

        if (temp == 0) {
            
            switch (index) {
                case 0:
                    sprite1.init(0, -1, 1, 1); // Esquina inferior der
					sprite2.init(-1, 0, 1, 1);
                    break;
                case 1:
                    sprite1.init(0, 0, 1, 1); // Esquina superior der
					sprite2.init(-1, -1, 1, 1);
                    break;
                case 2:
                    sprite1.init(-1, 0, 1, 1); // Esquina superior izq
					sprite2.init(0, -1, 1, 1);
                    break;
                case 3:
                    sprite1.init(-1, -1, 1, 1); // Esquina inf izquierda
					sprite2.init(0, 0, 1, 1);
                    break;
            }

			if(index<4)
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
	while (SDL_PollEvent(&event)){
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

	program.linkShader();

}
