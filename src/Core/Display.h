#pragma once

#include "pch.h"

#include "Scene/Scene.h"

namespace ForestHunt::Display {

    static inline GLFWwindow* s_WindowPtr = nullptr;
    static inline uint32_t s_CurrentFps = 0;

    void CreateDisplay(std::shared_ptr<Scene> scenePtr);

    inline float GetCurrentFps() { return s_CurrentFps; }

}