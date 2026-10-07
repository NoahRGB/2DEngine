#version 330 core

in vec2 vLocal;

out vec4 FragColor;

uniform vec4 uColour;

void main() {
    // vLocal is between -0.5 and 0.5
    // so length(vLocal) is between 0 and 1
    // (length * 2) means lengths is between 0 and 2
    // (1 - length) means distance is between -1 and 1

    float distance = 1.0 - length(vLocal) * 2.0;

    float alpha = smoothstep(0.0, 0.02, distance);

    FragColor = vec4(uColour.xyz, uColour.a * alpha);
}