#version 410 core

layout(location = 0) in vec3 aPosition;

void main() {
    gl_Position.xyz = aPosition;
    gl_Position.w = 1.0;
}