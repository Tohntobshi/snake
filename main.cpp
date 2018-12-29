#include "gameWindow.h"
#include <iostream>
#include <functional>
#include "world.h"
#include "snake.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#else
#include <thread>
#include <chrono>
#endif

void clearGlErrors();
void checkGLErrors();


std::function<void ()> iterate;
void callIterate()
{
  iterate();
}

int main(int argc, char const *argv[])
{
  clearGlErrors();
  GameWindow gameWindow = { 640, 480 };
  World world = { 20.0f, 15.0f };
  Snake snake = { 20, 15 };
  world.addModel("red_square", 1.0f, 0.0f, 0.0f);
  world.addModel("green_square", 0.0f, 1.0f, 0.0f);
  iterate = [&]()
  {
    world.clearScreen();
    world.clearObjectPositions();
    int key = gameWindow.getKey();
    snake.update(key);
    for (int x = 0; x < snake.width; x++)
    {
      for (int y = 0; y < snake.height; y++)
      {
        if (snake.playground[x][y].type == body)
        {
          world.addPosition("green_square", (float)x + 0.5f, (float)y + 0.5f);
        }
        if (snake.playground[x][y].type == food)
        {
          world.addPosition("red_square", (float)x + 0.5f, (float)y + 0.5f);
        }
      }
    }
    world.draw();
    gameWindow.swapBuffers();
  };
  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(callIterate, 5, 1);
  #else
  while(true) {
    iterate();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  #endif
  return 0;
}
