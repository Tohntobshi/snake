#include "gameWindow.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


GameWindow::GameWindow(int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(width, height, "Hello", nullptr, nullptr);
    glfwSetKeyCallback(window, keyCallback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    glewInit();
}
GameWindow::~GameWindow()
{
  glfwTerminate();
}

void GameWindow::swapBuffers()
{
  glfwSwapBuffers(window);
  
}


int GameWindow::getKey() {
  glfwPollEvents();
  int key = lastKey;
  lastKey = 0;
  return key;
}

void GameWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  lastKey = key;
}

int GameWindow::lastKey = 0;