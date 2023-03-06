cmake_minimum_required(VERSION 3.16)
project(GraphicsAPITestProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS "-Ofast")

add_executable(GraphicsAPITestProject GraphicsAPITestMain.cpp Command.h CommandProcessor.h CompositeDrawShapeCommand.h DrawingCanvas.h DrawingProcessor.h DrawShapesCommands.h)

target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -lpthread)
