
set (target "XE.Demo")
set (sources "Demo.cpp")

add_executable(${target} ${sources})

include_directories(.)

target_link_libraries(${target} XE.Core XE.IO XE.Graphics.GL XE.Graphics.GL.GLFW)
