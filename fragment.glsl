#version 330 core

int vec3 fragmentColor;

out vec3 color;

void main() {
    color = fragmentColor;
}