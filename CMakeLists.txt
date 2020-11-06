cmake_minimum_required(VERSION 3.17)
project(FlappyBird_WinAPI)

set(CMAKE_CXX_STANDARD 20)

add_executable(FlappyBird_WinAPI main.cpp Flappy.h Game/Game.cpp Game/Game.h Game/Scene.cpp Game/Scene.h Bird/Bird.cpp Bird/Bird.h Game/GameState.cpp Game/GameState.h)

set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")