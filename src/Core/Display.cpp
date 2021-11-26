#include "Display.h"

using namespace ForestHunt;

static constexpr bool ENABLE_V_SYNC = true;

static const char* GAME_NAME = "Forest Hunt";
static const char* GAME_VERSION = "v1.0";

static void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Display::CreateDisplay(std::function<void(float)> function) {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    std::stringstream titleStream;
    titleStream << GAME_NAME << " " << GAME_VERSION;

    s_WindowPtr = glfwCreateWindow(1600, 900, titleStream.str().c_str(), NULL, NULL);

    if(s_WindowPtr == NULL) {
        std::cout << "Failed to create the window!" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(s_WindowPtr);
    glfwSetFramebufferSizeCallback(s_WindowPtr, FrameBufferSizeCallback);

    glfwSwapInterval(ENABLE_V_SYNC);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD!" << std::endl;
        return;
    }

    // Game Loop

    float endTime, startTime = (float) glfwGetTime();
    float deltaTime = 0.0f;
    float accumulativeDeltaTime = 0.0f;

    uint32_t frameCount = 0;

    while(!glfwWindowShouldClose(s_WindowPtr)) {
        // Input

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Update
        if(deltaTime >= 0) {
            function(deltaTime);
        }

        glfwSwapBuffers(s_WindowPtr);
        glfwPollEvents();

        endTime = (float) glfwGetTime();
        deltaTime = endTime - startTime;
        startTime = endTime;

        accumulativeDeltaTime += deltaTime;
        if(accumulativeDeltaTime >= 1.0) {
            s_CurrentFps = frameCount;

            std::stringstream titleStream;
            titleStream << GAME_NAME << " " << GAME_VERSION << " | " << s_CurrentFps << " FPS";

            glfwSetWindowTitle(s_WindowPtr, titleStream.str().c_str());

            frameCount = 0;
            accumulativeDeltaTime = 0.0f;
        }

        frameCount++;
    }

    glfwTerminate();
}