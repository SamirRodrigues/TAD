cmake_minimum_required(VERSION 3.5)
project(TestManagerVector VERSION 0.1 LANGUAGES CXX )

# set the compiling flags
set ( CMAKE_CXX_FLAGS "-Wall" )

#--------------------------------
# This is for old cmake versions
#set (CMAKE_CXX_STANDARD 11)
#--------------------------------

### [1] Test target
# set the include path
include_directories( include
                    src/lib )

# Add the test target
add_executable( run_tests
                src/lib/test_manager.cpp
                src/test/run_tests.cpp )

# define C++11 standard
set_property(TARGET run_tests PROPERTY CXX_STANDARD 11)


# The end
