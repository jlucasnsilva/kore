#version 330 core

layout(location = 0) in vec3 model;
layout(location = 1) in vec3 color;

uniform mat4 MVP;
uniform mat4 ROT;

out vec3 fragmentColor;

void main() {
    gl_Position = MVP * ROT * vec4(model, 1.0);
    fragmentColor = color;
}
