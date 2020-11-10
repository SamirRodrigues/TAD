# TAD
In this project, a sequential container with a dynamic vector was implemented.

This project was proposed by professor Selan Rodrigues from UFRN, for EDB1 material from the IT course. And developed by students / authors Samir Rodrigues and Italo Lima.

To compile this project with [cmake](https://cmake.org) follow these steps:

1. `cd TAD`: enters into the main project directory.
2. `cmake -S . -Bbuild`:  asks cmake to create the build directory and generate the Unix Makefile based on the script found in `CMakeLists.txt`, on the current level.
3. `cd build`: enter the build folder.
4. `cmake --build .` or `make`: triggers the compiling process.


To run with our tests, first follow the compilation step above, then run inside the folder  `cd TAD/build` the command  `./play`.


Comments
1. A variation of the tests created by Felipe C Ramos (git @FelipeRCramos) was used in this project.
2. The use of this code is free, for any purpose, please credit if you use them.
3. Project Authors Samir Rodrigues and Italo Lima. (gits @SamirRodrigues & @italo-ce)