#version 330 core

layout (location = 0) in vec3 aPos;

out vec2 vLocal;

uniform mat4 uModel;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uModel * vec4(aPos, 1.0f);
    vLocal = vec2(aPos);
}