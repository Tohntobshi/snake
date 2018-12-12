#include <list>

struct occurence {
  float x;
  float y;
};

class Model
{
  public:
  unsigned int vao;
  std::list<occurence> occurences;
  Model(unsigned int shader, float red, float green, float blue);
  ~Model();
  unsigned int vbo;
  unsigned int ebo;
  void bind();
  void draw();
};