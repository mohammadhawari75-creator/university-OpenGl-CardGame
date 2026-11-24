cmake_minimum_required(VERSION 3.20)
project(GLSolution CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Find system OpenGL
find_package(OpenGL REQUIRED)

#-------------------------------------------------------------------------------
# OpenGL.SharedModule (Static Library)
# Only what this project uses: glad (OpenGL function loader) and stb_image (image loading).
#-------------------------------------------------------------------------------
add_library(OpenGL.SharedModule STATIC
    OpenGL.SharedModule/src/glad.c
    OpenGL.SharedModule/src/stb_image.cpp
)

target_include_directories(OpenGL.SharedModule PUBLIC
    OpenGL.SharedModule/dependencies/include
    OpenGL.SharedModule/dependencies/include/glad
    OpenGL.SharedModule/dependencies/include/GLFW
)

target_link_libraries(OpenGL.SharedModule PUBLIC
    OpenGL::GL
)

# Automatically find all .cpp and .c files in the GLProject folder (and one level of sub-folders)
file(GLOB GLPROJECT_SOURCES
    "GLProject/*.cpp"
    "GLProject/*.c"
    "GLProject/**/*.cpp"
    "GLProject/**/*.c"
)

add_executable(GLProject
    ${GLPROJECT_SOURCES}
    OpenGL.SharedModule/src/glad.c
)

# MinGW (Windows): put the C++ runtime inside the .exe, so it cannot load a different
# libstdc++-6.dll from another program in PATH (that causes crashes when strings are destroyed).
if(MINGW)
    target_link_options(GLProject PRIVATE -static-libgcc -static-libstdc++)
endif()

link_directories(OpenGL.SharedModule/dependencies/libs)

target_include_directories(GLProject PRIVATE
    GLProject
    OpenGL.SharedModule/dependencies/include
    OpenGL.SharedModule/dependencies/include/GLFW
    OpenGL.SharedModule/dependencies/include/glad
)

if(WIN32)
target_link_libraries(GLProject PRIVATE
    OpenGL.SharedModule
    glfw3
    OpenGL::GL
)
else()
target_link_libraries(GLProject PRIVATE
    OpenGL.SharedModule
    glfw
    OpenGL::GL
)
endif()

# Copy shaders and textures next to the executable
add_custom_command(
    TARGET GLProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/GLProject
            $<TARGET_FILE_DIR:GLProject>
    COMMENT "Syncing GLProject directory contents and assets to build output..."
)
