# snake
Snake game. My first steps with cpp and opengl.

to build as linux desktop app run
cmake . && make

to build as web app (emscripten should be set) run
emcc main.cpp gameWindow.cpp model.cpp world.cpp glErrChecks.cpp snake.cpp -s USE_SDL=2 -std=c++17 -Os --closure 1 -s ENVIRONMENT=web -o ./dist/a.out.js
