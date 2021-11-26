#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aTint;

uniform mat4 uProjectionViewMatrix;

out vec4 vTint;

void main() {
    vTint = aTint;

    gl_Position = uProjectionViewMatrix * vec4(aPosition, 1.0);
}