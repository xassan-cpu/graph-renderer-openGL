
cmake_minimum_required(VERSION 3.20)

Project(OpenGLTemplate)

# Collect all source and header files in src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h src/*.hpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# === External Libraries ===

# GLFW
set(GLFW_DIR external/glfw)
add_subdirectory(${GLFW_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_DIR}/include)

# GLAD
set(GLAD_DIR external/glad)
add_subdirectory(${GLAD_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${GLAD_DIR}/include)

# STB_IMAGE
set(STB_DIR external/stb_image)
target_sources(${PROJECT_NAME} PRIVATE ${STB_DIR}/stb_image.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${STB_DIR})

# GLM
set(GLM_DIR external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${GLM_DIR})

# === Platform-specific OpenGL linking ===
if (WIN32)
    set(OPENGL_LIBS opengl32)
else()
    find_package(OpenGL REQUIRED)
    set(OPENGL_LIBS OpenGL::GL)
endif()

# === Link libraries ===
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad ${OPENGL_LIBS})
