# Abstract Data Type Vector
An C++ Abstract Data Type implementation (alike std::vector)

# Objectives
In this project, we aim to get a similar implementation of the STL equivalent
*[std::vector](http://www.cplusplus.com/reference/vector/vector/)*.
Just like arrays, vectors use contiguos storage locations for their elements, 
which means that their elements can also be acessed using offsets on regular 
pointers to its elements, and just as efficiently as in arrays. But unlike 
arrays, their size can change dynamically, with their storage being handled 
automatically by the container.

# Compile
Since the objective of this project isn't to create a main program, but 
instead, create a lib that can be used to create client's codes, we will 
teach first how to include the lib inside your project.

1. Download source code from this project, you can do it by cloning the git, 
downloading the zip, using wget...
2. Copy the source code to your source code corresponding folder inside your 
project.
3. Copy the header file to your corresponding include folder inside your 
project.
4. Compile your project making the correct links to the include files and 
adding `#include "vector.hpp"` on your header.

## Compile for this test
In order to test if the implementation is correct, we made a little main 
program to simulate the client code and test all lib's features.

You can compile it by entering in the project folder inside your computer (i'
ll teach on linux/unix based distros) and executing on the terminal:
```bash
# To compile
make
```

### Execute
To execute the test code, just type:
```bash
./tad-vector
```
while on the root folder of the project.


# Other features
*TODO*

# Authorship
All codes here we're made by Felipe Ramos and Max William, for a project on 
the Basic Data Structure I course on UFRN. All codes here are under the MIT 
License.
