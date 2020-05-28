#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D hextex;

void main() {
    color = texture(hextex, UV).rgb;
}
