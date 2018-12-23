#pragma once
#include <SDL2/SDL.h>


class GameWindow
{
private:
  SDL_Window* window;
  SDL_GLContext context;
public:
  GameWindow(int width, int height);
  ~GameWindow();
  void swapBuffers();
  int getKey();
};
