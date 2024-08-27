cmake_minimum_required(VERSION 3.28)
project(Minecraft)

set(CMAKE_CXX_STANDARD 11)

add_executable(Minecraft main.cpp
        sources/Camera.cpp
        include/glad.c
        sources/helper.cpp
        sources/Shader.cpp
        sources/stb_image.cpp
        sources/GrassCube.cpp
        headers/GrassCube.h
        headers/constants.h
        sources/CubesContainer.cpp
        headers/CubesContainer.h
        sources/Player.cpp
        headers/Player.h
        sources/Sphere.cpp
        headers/Sphere.h
        sources/SkyBox.cpp
        headers/SkyBox.h
        sources/Plane.cpp
        headers/Plane.h
        sources/PhysicsWorld.cpp
        headers/PhysicsWorld.h
        headers/frameTime.h
        sources/FirstPersonController.cpp
        headers/FirstPersonController.h
        sources/RayCast.cpp
        headers/RayCast.h
        sources/CubeBorder.cpp
        headers/CubeBorder.h
        sources/CrossAir.cpp
        headers/CrossAir.h)



target_include_directories(Minecraft PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Minecraft GL sfml-graphics sfml-window sfml-system)
