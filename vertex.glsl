#version 330 core

layout(location = 0) in vec3 model;
layout(location = 1) in vec3 color;

uniform mat4 MVP;

out vec3 fragmentColor;

void main() {
    gl_Position = MVP * vec4(model, 1.0);
    fragmentColor = color;
}
