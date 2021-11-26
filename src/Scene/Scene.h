#pragma once

#include "pch.h"

#include "Render/Camera.h"

namespace ForestHunt {

    class Scene;

    class SceneManager {

    public:
        static std::shared_ptr<Camera> GetActiveSceneCamera();

        static void SetScene(std::shared_ptr<Scene> scenePtr);

        static void OnUpdate(float deltaTime);
        static void OnDestroy();

    private:
        static inline std::shared_ptr<Scene> s_ScenePtr = nullptr;

    };

    class Scene {

        friend class SceneManager;

    public:
        virtual void OnCreate() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnDestroy() {}

    protected:
        std::shared_ptr<Camera> m_Camera = std::make_shared<Camera>();

    };

}