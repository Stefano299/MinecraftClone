cmake_minimum_required(VERSION 3.28)
project(Minecraft)

set(CMAKE_CXX_STANDARD 11)

add_executable(Minecraft main.cpp
        Camera.cpp
        glad.c
        helper.cpp
        Shader.cpp
        stb_image.cpp
        GrassCube.cpp
        GrassCube.h
        constants.h
        CubesContainer.cpp
        CubesContainer.h
        Player.cpp
        Player.h
        Sphere.cpp
        Sphere.h
        SkyBox.cpp
        SkyBox.h
        Plane.cpp
        Plane.h
        PhysicsWorld.cpp
        PhysicsWorld.h
        frameTime.h
        FirstPersonController.cpp
        FirstPersonController.h
        RayCast.cpp
        RayCast.h
        CubeBorder.cpp
        CubeBorder.h
        CrossAir.cpp
        CrossAir.h)



target_include_directories(Minecraft PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Minecraft GL sfml-graphics sfml-window sfml-system)
