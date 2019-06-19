I think G++ was already installed with ubuntu 19.04 but if not type: sudo apt install g++

To create a txt file in consol: cat > README.txt

To compile the SDL main file use: g++ 01_hello_SDL.cpp -w -lSDL2 -o 01_hello_SDL
To run the complied code type: ./01_hello_SDL

A way to shortcut the long command each time to compile the code is to use the makefile. To use the makefile to complie the code just use: make all      //ensure the file is saved as 'makefile' or use:make -f filename


Add transparency to text:
convert image.png -alpha set -channel a -evaluate set 65% +channel newimage.png

Make sure to change the header file FOR LINUX to: #include <SDL2/SDL.h>

Installing SDLimage 2
apt-cache search libsdl2-image
apt-get install libsdl2-image-dev

g++ Main.cpp Game.cpp CheckerManager.cpp GameObject.cpp TextureManager.cpp -w -lSDL2 -lSDL2_image -o main
//-o is the output file to put the executable, -w includes the linkers, and all the cpp files are needed to be compiled.

//TODO:
Update make file to work.

git reset --hard 0d1d7fc32
