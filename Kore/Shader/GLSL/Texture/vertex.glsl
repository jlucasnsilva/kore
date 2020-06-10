#version 330 core

layout(location = 0) in vec3 model;
layout(location = 1) in vec2 vertexUV;

uniform mat4 Transform;

out vec2 UV;

void main() {
    gl_Position = Transform * vec4(model, 1.0);
    UV = vertexUV;
}
