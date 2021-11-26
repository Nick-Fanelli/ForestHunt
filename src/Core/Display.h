#pragma once

#include "pch.h"

namespace ForestHunt::Display {

    static inline GLFWwindow* s_WindowPtr = nullptr;
    static inline uint32_t s_CurrentFps = 0;

    void CreateDisplay(std::function<void()> initPtr, std::function<void(float)> updatePtr);

    inline float GetCurrentFps() { return s_CurrentFps; }

}