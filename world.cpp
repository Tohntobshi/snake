#include "world.h"
#include <SDL2/SDL_opengles2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


void clearGlErrors();
void checkGLErrors();


World::World(float width, float height)
{ 
  const char* vertexSource = R"glsl(
    attribute vec2 position;
    attribute vec3 color;
    varying vec3 Color;
    uniform mat4 viewProj;
    uniform mat4 model;
    void main()
    {
      Color = color;
      gl_Position = viewProj * model * vec4(position, 0.0, 1.0);
    }
  )glsl";
  const char* fragmentSource = R"glsl(
    precision mediump float;
    varying vec3 Color;
    void main()
    {
      gl_FragColor = vec4(Color, 1.0);
    }
  )glsl";
  // Create and compile the vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  
  // Create and compile the fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  
  // Link the vertex and fragment shader into a shader program
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glUseProgram(shaderProgram);

  int viewProjUniform = glGetUniformLocation(shaderProgram, "viewProj");
  glm::mat4 proj = glm::ortho(0.0f, width, 0.0f, height);
  glUniformMatrix4fv(viewProjUniform, 1, GL_FALSE, glm::value_ptr(proj));
  modelUniform = glGetUniformLocation(shaderProgram, "model");
}

World::~World()
{
  glDeleteProgram(shaderProgram);
  glDeleteShader(fragmentShader);
  glDeleteShader(vertexShader);
  for(auto& object: objects)
  {
    delete object.second;
  }
}

void World::addModel(std::string name, float red, float green, float blue)
{
  Model* ptr = new Model(shaderProgram, red, green, blue);
  // dont forget to delete them in world's destructor
  objects.insert({ name, ptr });
}

void World::addPosition(std::string name, float x, float y)
{
  auto it = objects.find(name);
  it->second->occurences.push_back({ x, y });
}

void World::draw()
{
  for(auto& object: objects)
  {
    object.second->bind();
    for(auto& occurence: object.second->occurences)
    {
      // std::cout << "x " << occurence.x << " y " << occurence.y << std::endl;
      glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(occurence.x, occurence.y, 0.0f));
      glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(translate));
      object.second->draw();
    }
  }
}

void World::clearScreen()
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  
}

void World::clearObjectPositions()
{
  for(auto& object: objects)
  {
    object.second->occurences.clear();
  }
}