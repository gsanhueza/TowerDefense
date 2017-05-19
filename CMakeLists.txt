cmake_minimum_required (VERSION 2.8)
project(TowerDefense)

# specify which version you need
find_package(OGRE 1.10 REQUIRED)

# the search paths
include_directories(${OGRE_INCLUDE_DIRS})
link_directories(${OGRE_LIBRARY_DIRS})

# copy essential config files next to our binary where OGRE autodiscovers them
# file(COPY ${OGRE_CONFIG_DIR}/plugins.cfg ${OGRE_CONFIG_DIR}/resources.cfg
#      DESTINATION ${CMAKE_BINARY_DIR})

set (HDRS
#     include/test.h
)

set (SRCS
    src/main.cpp
)

add_executable(TowerDefense ${HDRS} ${SRCS})
target_link_libraries(TowerDefense ${OGRE_LIBRARIES})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
