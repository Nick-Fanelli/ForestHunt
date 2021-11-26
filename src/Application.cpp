#include <pch.h>

#include "Core/Display.h"

using namespace ForestHunt;

static void Update(float deltaTime) {

    // std::cout << deltaTime << std::endl;

}

int main() {

    Display::CreateDisplay(Update);    

}