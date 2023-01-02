CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(testgamework C)

add_executable(testgamework test.c)

target_include_directories(testgamework PRIVATE "../")
target_include_directories(testgamework PRIVATE "../deps/glfw/include")
target_include_directories(testgamework PRIVATE "../deps/glad")

target_link_directories(testgamework PUBLIC "../deps/glfw/bin/win32")
target_link_libraries(testgamework PRIVATE glfw3.dll)
