#pragma once

#include "model.h"
#include <string>
#include <map>


class World
{
  public:
  unsigned int vertexShader;
  unsigned int fragmentShader;
  unsigned int shaderProgram;
  int modelUniform;
  std::map<std::string, Model*> objects;
  World(float width, float height);
  ~World();
  void addModel(std::string name, float red, float green, float blue);
  void addPosition(std::string name, float x, float y);
  void draw();
  void clearObjectPositions();
  void clearScreen();
};