#include "Display.h"

using namespace ForestHunt;

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Display::CreateDisplay() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    s_WindowPtr = glfwCreateWindow(1600, 900, "Forest Hunt", NULL, NULL);

    if(s_WindowPtr == NULL) {
        std::cout << "Failed to create the window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(s_WindowPtr);
    glfwSetFramebufferSizeCallback(s_WindowPtr, FrameBufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Game Loop
    while(!glfwWindowShouldClose(s_WindowPtr)) {
        // Input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(s_WindowPtr);
        glfwPollEvents();
    }

    glfwTerminate();
}