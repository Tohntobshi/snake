#include "model.h"
#include <GL/glew.h>
#include <iostream>

void clearGlErrors();
void checkGLErrors();


Model::Model(unsigned int shader, float red, float green, float blue)
{
  // Create Vertex Array Object
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  std::cout << "model constructor call" << std::endl;
  float vertices[] = {
    -0.5f,  0.5f, red, green, blue, // Top-left
    0.5f,  0.5f, red, green, blue, // Top-right
    0.5f, -0.5f, red, green, blue, // Bottom-right
    -0.5f, -0.5f, red, green, blue, // Bottom-left
  };
  unsigned int elements[] = {
    0, 1, 2,
    2, 3, 0
  };

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  // Specify the layout of the vertex data
  int posAttrib = glGetAttribLocation(shader, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
  
  int colorAttrib = glGetAttribLocation(shader, "color");
  glEnableVertexAttribArray(colorAttrib);
  glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
}

Model::~Model()
{
  std::cout << "model destructor call" << std::endl;
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
}

void Model::bind()
{
  glBindVertexArray(vao);
}

void Model::draw()
{
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}