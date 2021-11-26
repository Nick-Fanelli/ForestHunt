#pragma once

#include "pch.h"

#include "Scene.h"

namespace ForestHunt {

    class GameScene : public Scene {

    public:

        GameScene() = default;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnDestroy() override;

    };

}