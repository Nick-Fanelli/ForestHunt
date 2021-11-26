#include <pch.h>

#include "Core/Display.h"

#include "Render/Shader.h"
#include "Render/QuadRenderer.h"

using namespace ForestHunt;

static QuadRenderer s_QuadRenderer;

static void Init() {

    s_QuadRenderer.Initialize();

}

static void Update(float deltaTime) {

    s_QuadRenderer.StartBatch();

    s_QuadRenderer.DrawQuad({-1.0f, -1.0f, 0.0f });

    s_QuadRenderer.EndBatch();

}

int main() {

    Display::CreateDisplay(Init, Update);    

}