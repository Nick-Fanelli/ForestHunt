#pragma once

#include "pch.h"

namespace ForestHunt {

    class Scene;

    class SceneManager {

    public:
        static void SetScene(std::shared_ptr<Scene> scenePtr);

        static void OnUpdate(float deltaTime);
        static void OnDestroy();

    private:
        static inline std::shared_ptr<Scene> s_ScenePtr = nullptr;

    };

    class Scene {

    public:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}

    };

}