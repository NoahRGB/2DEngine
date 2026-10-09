#include "Rect.h"

Rect::Rect() {

}

void Rect::setupGeometry() {

    float quadVertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int quadIndices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glGenBuffers(1, &this->ebo);
    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Rect::draw(Shader* shader, glm::mat4 trans, glm::mat4 proj, glm::vec4 colour, Texture* texture) {
    shader->enable();
    shader->setMat4f("uModel", trans);
    shader->setMat4f("uProjection", proj);
    shader->setVec4f("uColour", colour);

    if (texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture->textureId);
        shader->setInt("uTexture", 0);
    }

    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}