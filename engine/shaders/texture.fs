#version 330 core

in vec2 vLocal;

out vec4 FragColor;

uniform sampler2D uTexture;
uniform vec4 uColour;

void main() {
    // vLocal is between -0.5 and 0.5, shift to between 0 and 1 for texture coords
    vec2 uv = vLocal + 0.5;
    FragColor = texture(uTexture, uv) * uColour;
}