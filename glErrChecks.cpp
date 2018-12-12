#include <GL/glew.h>
#include <iostream>

void clearGlErrors()
{
    while(glGetError())
    {
        // do nothing
    }
}
void checkGLErrors()
{
    int err;
    while(err = glGetError())
    {
        std::cout << "Error " << std::hex << err << std::endl;
    }
}