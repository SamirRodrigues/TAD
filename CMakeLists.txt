cmake_minimum_required(VERSION 3.5)
project(TADVector VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )
set ( CMAKE_CXX_FLAGS "-g" )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 11)
#--------------------------------

### [1] Application target
# set the include path
include_directories( include )

# define the sources for the project
add_executable( play
                src/main.cpp # This has the application main().
                )

# define C++11 standard
set_property(TARGET play PROPERTY CXX_STANDARD 11)

# The end
