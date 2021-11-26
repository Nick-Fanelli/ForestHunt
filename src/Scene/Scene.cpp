#include "Scene.h"

using namespace ForestHunt;

void SceneManager::SetScene(std::shared_ptr<Scene> scenePtr) {
    if(s_ScenePtr != nullptr) {
        std::shared_ptr<Scene> oldScenePtr = s_ScenePtr;
        s_ScenePtr = nullptr;
        oldScenePtr->OnDestroy();
    }

    scenePtr->OnCreate();
    s_ScenePtr = scenePtr;
}

void SceneManager::OnUpdate(float deltaTime) {
    if(s_ScenePtr != nullptr)
        s_ScenePtr->OnUpdate(deltaTime);
}   

void SceneManager::OnDestroy() {
    if(s_ScenePtr != nullptr)
        s_ScenePtr->OnDestroy();
}