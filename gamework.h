#include <iostream>
#include <GLFW/glfw3.h>

void print_glfw_init()
{
    std::cout << glfwInit() << std::endl;
}

// Window stuff
struct WindowSpecs {
    unsigned int window_width, window_height;
    const char* window_title;
    bool window_fullscreen;

    unsigned int window_min_width, window_max_width, window_min_height, window_max_height;
    bool window_vsync;
};

void gameLoop();
double getGameUpTime();


#ifdef USING_GAMEWORK

void gameLoop(double timestep) {
    glfwPollEvents();
    glfwSwapBuffers();
}


#endif