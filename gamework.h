#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>

void print_glfw_init()
{
    printf("%d", glfwInit());
}

struct WindowSpecs {
    unsigned int window_width, window_height;
    const char* window_title;
    bool window_fullscreen;

    unsigned int window_min_width, window_max_width, window_min_height, window_max_height;
    bool window_vsync;
};