#include "gameWindow.h"
#define GL3_PROTOTYPES 1
#include <GL/glew.h>

GameWindow::GameWindow(int width, int height)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  window = SDL_CreateWindow( "SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL );
  context = SDL_GL_CreateContext(window);

  glewExperimental = GL_TRUE;
  glewInit();
}
GameWindow::~GameWindow()
{
  SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GameWindow::swapBuffers()
{
  SDL_GL_SwapWindow(window);
  
}


int GameWindow::getKey() {
  int lastKey = 0;
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    if(e.type == SDL_QUIT) {
      exit(0);
    }
    if(e.type == SDL_KEYDOWN) {
      
      lastKey = e.key.keysym.scancode;
    }
  }
  return lastKey;
}
