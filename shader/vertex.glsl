#version 330 core

layout(location = 0) in vec3 model;
layout(location = 1) in vec3 color;

uniform mat4 Transform;

out vec3 fragmentColor;

void main() {
    gl_Position = Transform * vec4(model, 1.0);
    fragmentColor = color;
}
