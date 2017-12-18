#/bin/bash
echo "Compiling...\n"
sudo g++ main.cc -lGLU -lGL -lglut -o run
echo "Done!\n" 
