#include "snake.h"
#include <cstdlib>
#include <iostream>

Point::Point()
{
  type = empty;
  positionInSnake = 0;
}
Point::Point(PointType t, int pos)
{
  type = t;
  positionInSnake = pos;
}

Snake::Snake(int w, int h)
{
  width = w;
  height = h;
  direction = left;
  length = 1;
  x = w / 2;
  y = h / 2;
  playground = new Point*[width];
  for(int i = 0; i < width; ++i) {
    playground[i] = new Point[height];
  }
  genFood();
}

Snake::~Snake()
{
  for(int i = 0; i < width; ++i) {
    delete [] playground[i];
  }
  delete [] playground;
}

void Snake::genFood()
{
  int nextFoodX;
  int nextFoodY;
  do
  {
    nextFoodX = std::rand() % width;
    nextFoodY = std::rand() % height;
  } while (x == nextFoodX || y == nextFoodY || playground[nextFoodX][nextFoodY].type != empty);
  playground[nextFoodX][nextFoodY].type = food;
}

void Snake::update(int command)
{
  // change direction
  if (command == 87 && direction != down)
    direction = up;
  else if (command == 83 && direction != up)
    direction = down;
  else if (command == 65 && direction != right)
    direction = left;
  else if (command == 68 && direction != left)
    direction = right;
  // move head
  switch (direction)
  {
  case right:
    x++;
    break;
  case left:
    x--;
    break;
  case up:
    y++;
    break;
  case down:
    y--;
    break;
  }
  if (x > width - 1)
    x -= width;
  if (y > height - 1)
    y -= height;
  if (x < 0)
    x += width;
  if (y < 0)
    y += height;
  // check food
  if (playground[x][y].type == food)
  {
    length++;
    genFood();
  }
  if (playground[x][y].type == body)
  {
    exit(1);
  }
  // update points
  for (int px = 0; px < width; px++)
  {
    for (int py = 0; py < height; py++)
    {
      if (x == px && y == py)
      {
        playground[px][py].positionInSnake = 0;
        playground[px][py].type = body;
      }
      else if (playground[px][py].type == body && playground[px][py].positionInSnake < length - 1)
      {
        playground[px][py].positionInSnake++;
        playground[px][py].type = body;
      }
      else if (playground[px][py].type == body && playground[px][py].positionInSnake >= length - 1)
      {
        playground[px][py].positionInSnake = 0;
        playground[px][py].type = empty;
      }
    }
  }
}