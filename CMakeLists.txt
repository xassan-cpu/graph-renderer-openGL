cmake_minimum_required(VERSION 3.20)

project(GraphRenderer)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/core/shader/shader.cpp
    src/core/texture/texture.cpp
    src/core/gl_utils/gl_utils.cpp
    src/engine/camera/camera.cpp
    src/engine/mesh/mesh.cpp
    src/engine/mesh_utils/meshutils.cpp
    src/gui/gui.cpp
    src/app/app.cpp
    src/renderer/renderer.cpp
    src/graph/graph.cpp
    src/graph/function_library.cpp
)

# Header files
set(HEADERS
    src/core/shader/shader.hpp
    src/core/texture/texture.hpp
    src/core/gl_utils/gl_utils.hpp
    src/engine/camera/camera.hpp
    src/engine/mesh/mesh.hpp
    src/engine/mesh_utils/meshutils.hpp
    src/gui/gui.hpp
    src/app/app.hpp
    src/renderer/renderer.hpp
    src/core/constants.hpp
    src/core/gl_includes.hpp
    src/graph/graph.hpp
    src/graph/function_library.hpp
)

set(SHADER_SOURCES
    res/shaders/basic.vert.glsl
    res/shaders/basic.frag.glsl
)

list(APPEND SOURCES ${HEADERS})

# === ImGui Setup ===

set(IMGUI_DIR external/imgui)

# Add ImGui implementation files to the sources
file(GLOB IMGUI_SOURCES "${IMGUI_DIR}/*.cpp")
list(FILTER IMGUI_SOURCES EXCLUDE REGEX ".*_impl_.*\\.cpp") # Exclude backend-specific implementation files

# Manually include the necessary backend files for GLFW and OpenGL3
set(IMGUI_BACKEND_SOURCES
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Append ImGui source files and backend files to the SOURCES list
list(APPEND SOURCES ${IMGUI_SOURCES} ${IMGUI_BACKEND_SOURCES})

# === Create Executable ===

# Create the executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${SHADER_SOURCES})

# Add ImGui include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Define the OpenGL loader for ImGui (using GLAD)
target_compile_definitions(${PROJECT_NAME} PRIVATE "IMGUI_IMPL_OPENGL_LOADER_GLAD")

# === External Libraries ===

# GLFW
set(GLFW_DIR external/glfw)
add_subdirectory(${GLFW_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/include)

# GLAD (OpenGL loader)
set(GLAD_DIR external/glad)
add_subdirectory(${GLAD_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_DIR}/include)

# STB_IMAGE (for image loading)
set(STB_DIR external/stb_image)
target_sources(${PROJECT_NAME} PRIVATE ${STB_DIR}/stb_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${STB_DIR})

# GLM (math library)
set(GLM_DIR external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

# === Platform-specific OpenGL linking ===
if (WIN32)
  set(OPENGL_LIBS opengl32)
else()
  find_package(OpenGL REQUIRED)
  set(OPENGL_LIBS OpenGL::GL)
endif()

# === Link libraries ===
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad ${OPENGL_LIBS})

# === Build Setup ===

# Place the executable in build/bin/
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy shaders to the build directory after building the project
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders)

# Copy textures to the build directory after building the project
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures)
