#include <pch.h>

#include "Core/Display.h"

#include "Render/Shader.h"
#include "Render/QuadRenderer.h"

#include "Scene/GameScene.h"

using namespace ForestHunt;

int main() {
    Display::CreateDisplay(std::make_shared<GameScene>());
}