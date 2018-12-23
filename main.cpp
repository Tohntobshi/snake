#include "gameWindow.h"
#include <iostream>
#include "world.h"
#include "snake.h"
#include <thread>
#include <chrono>

void clearGlErrors();
void checkGLErrors();

int main(int argc, char const *argv[])
{
  clearGlErrors();
  GameWindow gameWindow = { 640, 480 };
  World world = { 20.0f, 15.0f };
  Snake snake = { 20, 15 };
  world.addModel("red_square", 1.0f, 0.0f, 0.0f);
  world.addModel("green_square", 0.0f, 1.0f, 0.0f);
  while(true) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  return 0;
}
