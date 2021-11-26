#version 410 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aTint;

out vec4 vTint;

void main() {
    vTint = aTint;

    gl_Position.xyz = aPosition;
    gl_Position.w = 1.0;
}