#version 330 core

layout(location = 0) in vec3 model;

uniform mat4 Transform;

void main() {
    gl_Position = Transform * vec4(model, 1.0);
}
