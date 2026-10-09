#pragma once

#include "Shader.h"
#include "Texture.h"

class Rect {

    public:
        Rect();

        void setupGeometry();
        void draw(Shader* shader, glm::mat4 trans, glm::mat4 proj, glm::vec4 colour, Texture* texture = nullptr);

        unsigned int vao, vbo, ebo;

    private:


};