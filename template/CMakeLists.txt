cmake_minimum_required(VERSION 3.1)
project(tp7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Search libraries
#find_package(OpenGL REQUIRED) # OpenGL
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
set(LIB_HEADERS ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${glm_INCLUDE_DIRS})
set(LIBS GL GLU GLEW ${GLUT_LIBRARIES} assimp)

# Add source files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
# Add header files
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/include/*.h
	${CMAKE_SOURCE_DIR}/include/*.hpp)

# Use headers
include_directories(include/ ${LIB_HEADERS} )
# Create executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
# Link libraries
target_link_libraries(${PROJECT_NAME} ${LIBS})
