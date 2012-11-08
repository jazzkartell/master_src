# The name of our project is "HELLO". CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (Master)

set(CMAKE_CXX_FLAGS " -w -g -Wall")
FIND_PACKAGE(PCL 1.3 REQUIRED COMPONENTS common io kdtree visualization)
find_package(VTK REQUIRED)
INCLUDE_DIRECTORIES(${Master_SOURCE_DIR} ${PCL_INCLUDE_DIRS})
LINK_DIRECTORIES(${Master_BINARY_DIR} ${PCL_LIBRARY_DIRS})
ADD_DEFINITIONS(${Master_Definitions} ${PCL_DEFINITIONS})

#add_executable (makeHash2D makeHash2D.cpp)
add_executable (makeHash3D makeHash3D.cpp)

#target_link_libraries (makeHash2D ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_KDTREE_LIBRARIES} ${VTK_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES})
target_link_libraries (makeHash3D ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_KDTREE_LIBRARIES} ${VTK_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES})
