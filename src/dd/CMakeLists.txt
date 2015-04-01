project(daydream)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(assimp REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)
# GLM

include_directories(
    ${CMAKE_SOURCE_DIR}/include/dd
    ${OPENGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
    ${assimp_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)

set(SOURCE_FILES
    Core/Util/FileWatcher.cpp
    Core/Camera.cpp
    Core/EventBroker.cpp
    Core/InputManager.cpp
    Core/Model.cpp
    Core/OBJ.cpp
    Core/PNG.cpp
    Core/Renderer.cpp
    Core/ResourceManager.cpp
    Core/ShaderProgram.cpp
    Core/Skeleton.cpp
    Core/Texture.cpp
    Core/World.cpp

    Input/InputSystem.cpp

    Particles/ParticleSystem.cpp

    Timer/TimerSystem.cpp

    Transform/TransformSystem.cpp

    Trigger/TriggerSystem.cpp
)

add_library(daydream ${SOURCE_FILES})
target_link_libraries(daydream
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${Boost_LIBRARIES}
    ${assimp_LIBRARIES}
    ${PNG_LIBRARIES}
)