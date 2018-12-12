typedef struct GLFWwindow GLFWwindow;

class GameWindow
{
private:
  GLFWwindow *window;
  
public:
  static int lastKey;
  GameWindow(int width, int height);
  ~GameWindow();
  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
  void swapBuffers();
  static int getKey();
};
