# The name of our project is "HELLO". CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (Master)

# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

#add_subdirectory (Hello)
#add_subdirectory (Demo) 

set(CMAKE_CXX_FLAGS " -w ")

find_package(PCL 1.3 REQUIRED COMPONENTS common io)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
#add_library (Master main.cpp) 

# Make sure the compiler can find include files from our Hello library.
#include_directories (${Master_SOURCE_DIR})

# Make sure the linker can find the Hello library once it is built.
#link_directories (${Master_BINARY_DIR})

# Add executable called "helloDemo" that is built from the source files
# "demo.cxx" and "demo_b.cxx". The extensions are automatically found.
add_executable (makeHash2D makeHash2D.cpp)
add_executable (makeHash3D makeHash3D.cpp)

# Link the executable to the Hello library.
target_link_libraries (makeHash2D ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
target_link_libraries (makeHash3D ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})
