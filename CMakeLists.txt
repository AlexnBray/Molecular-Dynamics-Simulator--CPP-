cmake_minimum_required(VERSION 3.16)

project(molecular_dynamics_sim
    VERSION 0.1.0
    DESCRIPTION "Real-time 2D molecular dynamics simulation with Lennard-Jones interactions and Velocity Verlet integration"
    LANGUAGES CXX
)

# ---- Language settings ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Default build type ----
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        Debug Release RelWithDebInfo MinSizeRel)
endif()

# Put binaries in a predictable location regardless of generator
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ---- Dependencies ----
# Requires SFML 2.5+ installed system-wide or via vcpkg/Conan.
# Linux:   sudo apt install libsfml-dev
# macOS:   brew install sfml
# Windows: pacman -S mingw-w64-ucrt-x86_64-sfml  (MSYS2 UCRT64)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# ---- Sources ----
set(SIM_SOURCES
    main.cpp
    particle.cpp
    utils.cpp
    grid_particle.cpp
    lj_potential.cpp
    velocity_velvet_int.cpp
)

set(SIM_HEADERS
    constants.h
    particles.h
    utils.h
    grid_particle.h
    lj_potential.h
    velocity_velvet_int.h
)

# ---- Main executable ----
add_executable(sim ${SIM_SOURCES} ${SIM_HEADERS})

target_link_libraries(sim PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(sim PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# ---- Compiler warnings ----
if(MSVC)
    target_compile_options(sim PRIVATE /W4 /permissive-)
else()
    target_compile_options(sim PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wshadow
        -Wnon-virtual-dtor
    )
endif()

# ---- Per-config optimization flags ----
target_compile_definitions(sim PRIVATE
    $<$<CONFIG:Debug>:SIM_DEBUG>
    $<$<CONFIG:Release>:SIM_RELEASE>
)

# ---- Copy runtime assets next to the executable ----
# main.cpp loads fonts/ via a relative path, so they must sit next to sim.exe
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/fonts)
    add_custom_command(TARGET sim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/fonts
            $<TARGET_FILE_DIR:sim>/fonts
        COMMENT "Copying fonts/ to build output"
    )
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/icons)
    add_custom_command(TARGET sim POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/icons
            $<TARGET_FILE_DIR:sim>/icons
        COMMENT "Copying icons/ to build output"
    )
endif()

# ---- Summary ----
message(STATUS "")
message(STATUS "=== ${PROJECT_NAME} v${PROJECT_VERSION} ===")
message(STATUS "Build type:    ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard:  ${CMAKE_CXX_STANDARD}")
message(STATUS "SFML version:  ${SFML_VERSION}")
message(STATUS "Output:        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message(STATUS "")
