#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include "Shader.h"
#include "load_texture.h"
#include "Object.h"
#include "Shelf.h"
#include "Container.h"

int Container::texture_box = 0;
int Container::texture_box_specular = 0;
unsigned int Container::VAO = 0;
unsigned int Container::VBO = 0;

float box[] = {
    // positions          // normals           // texture coords
    -0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.4f,  0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.4f, -0.4f, -0.4f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.4f, -0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.4f, -0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.4f,  0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.4f,  0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.4f,  0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.4f, -0.4f,  0.4f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.4f,  0.4f,  0.4f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.4f,  0.4f, -0.4f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.4f, -0.4f, -0.4f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.4f, -0.4f, -0.4f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.4f, -0.4f,  0.4f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.4f,  0.4f,  0.4f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.4f,  0.4f,  0.4f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.4f,  0.4f, -0.4f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.4f, -0.4f, -0.4f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.4f, -0.4f, -0.4f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.4f, -0.4f,  0.4f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.4f,  0.4f,  0.4f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.4f, -0.4f,  0.4f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.4f, -0.4f, -0.4f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.4f,  0.4f,  0.4f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.4f,  0.4f, -0.4f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

Container::Container(int x, int z, int des) {
    type = object_type::CONTAINER;
	Position = glm::vec3(x, 0.4 + GROUND, z);
    index = current_index;
	current_index++;
    depend = NULL;
    row = -1;
    column = -1;
    angle = 0.0;
    objects[index] = this;
    float* f = new float[4];
    f[0] = x - 0.4;
    f[1] = x + 0.4;
    f[2] = z - 0.4;
    f[3] = z + 0.4;
    territory[index] = f;
}

void Container::initial() {

    texture_box = loadTexture("pic/container2.png");
    texture_box_specular = loadTexture("pic/container2_specular.png");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Container::draw(Shader& shader) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, Position);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
    shader.use();
    shader.setMat4("model", model);
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 1);
    shader.setFloat("material.shiness", 32.0);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_box);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_box_specular);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    territory[index][0] = Position.x - 0.4;
    territory[index][1] = Position.x + 0.4;
    territory[index][2] = Position.z - 0.4;
    territory[index][3] = Position.z + 0.4;
}

void Container::SetAng(float Angle) {
    angle = Angle;
}

void Container::resetShelf() {
    if (depend) {
        ((Shelf*)depend)->reset(row, column);
        depend = NULL;
        row = -1;
        column = -1;
    }
}

void Container::setShelf(Object* i_shelf, int i_row, int i_column) {
    depend = i_shelf;
    row = i_row;
    column = i_column;
}