#pragma once

enum Direction
{
  left,
  right,
  up,
  down
};
enum PointType
{
  body,
  food,
  empty
};

class Point
{
  public:
  PointType type;
  int positionInSnake;
  Point();
  Point(PointType t, int pos);
};

class Snake
{
  private:
  void genFood();
  public:
  int width;
  int height;
  Point** playground;
  Direction direction;
  int x;
  int y;
  int length; 
  Snake(int width, int height);
  ~Snake();
  void update(int command);
  
};