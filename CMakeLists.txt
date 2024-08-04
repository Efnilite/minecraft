cmake_minimum_required(VERSION 3.28)
project(minecraft C)

set(CMAKE_C_STANDARD 23)

add_executable(minecraft main.c
        util/vec3.c
        util/vec3.h
        player.c
        player.h
        window.c
        window.h
        controls.c
        controls.h
        world/world.c
        world/world.h
        world/chunk.c
        world/chunk.h
        world/block.c
        world/block.h
        util/vec2.c
        util/vec2.h
)

find_package(SDL2 REQUIRED)
include_directories(minecraft ${SDL2_INCLUDE_DIRS})
target_link_libraries(minecraft ${SDL2_LIBRARIES} m)