cmake_minimum_required (VERSION 2.8)
project(TowerDefense)

# specify which version you need
find_package(OGRE 1.10 REQUIRED)

# the search paths
include_directories(${OGRE_INCLUDE_DIRS} include/)
link_directories(${OGRE_LIBRARY_DIRS})

# sources
set (SRCS
    src/Base.cpp
    src/main.cpp
)

# where to put the executable
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)

add_executable(TowerDefense ${SRCS})
target_link_libraries(TowerDefense ${OGRE_LIBRARIES})
