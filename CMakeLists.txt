cmake_minimum_required(VERSION 3.17)
project(FlappyBird_WinAPI)

set(CMAKE_CXX_STANDARD 20)

add_executable(FlappyBird_WinAPI WIN32 main.cpp Flappy.h Game/Game.cpp Game/Game.h Game/Scene/Scene.cpp Game/Scene/Scene.h Bird/Bird.cpp Bird/Bird.h Game/GameState.cpp Game/GameState.h Pipe/Pipe.cpp Pipe/Pipe.h Game/Shop/Shop.cpp Game/Shop/Shop.h Helper/Helper.cpp Helper/Helper.h)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++" )
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")