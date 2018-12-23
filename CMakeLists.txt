cmake_minimum_required(VERSION 2.8)
project( HelloGL )

find_package( OpenGL REQUIRED )

include_directories(${OPENGL_INCLUDE_DIR})

set(TARGETS main.cpp gameWindow.cpp model.cpp world.cpp glErrChecks.cpp snake.cpp)

add_executable( hellogl ${TARGETS} )

target_link_libraries(hellogl SDL2)
target_link_libraries(hellogl GLEW)
target_link_libraries(hellogl pthread)
target_link_libraries(hellogl ${OPENGL_gl_LIBRARY})


