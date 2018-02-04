#/bin/bash
echo "Compiling...\n"
sudo g++ clock.cc -lGLU -lGL -lglut -std=c++11 -o run
echo "Done!\n" 
