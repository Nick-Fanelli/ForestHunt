#include "GameScene.h"

#include "Render/QuadRenderer.h"

using namespace ForestHunt;

static QuadRenderer s_QuadRenderer;

void GameScene::OnCreate() {

    s_QuadRenderer.Initialize();

}

void GameScene::OnUpdate(float deltaTime) {

    s_QuadRenderer.StartBatch();

    s_QuadRenderer.DrawQuad({ -0.75f, 0.0f, 0.0f });
    s_QuadRenderer.DrawQuad({ 0.75f, 0.0f, 0.0f });

    s_QuadRenderer.EndBatch();
}

void GameScene::OnDestroy() {

}