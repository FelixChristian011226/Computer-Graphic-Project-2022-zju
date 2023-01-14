#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include "load_texture.h"
#include "shader.h"
#include "ground.h"


ground::ground(const std::string inputpic, const float vertices[], const int indices[]) {
    this->face = inputpic;
    for (int i = 0; i < GROUNDVSIZE; i++) this->groundVertices[i] = vertices[i];
    for (int i = 0; i < GROUNDISIZE; i++) this->groundIndices[i] = indices[i];
}
void ground::initial() {
    glGenVertexArrays(1, &fVAO);
    glGenBuffers(1, &fVBO);
    glGenBuffers(1, &fEB0);
    glBindVertexArray(fVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fEB0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(groundIndices), groundIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    this->texture_ground = loadTexture(face.c_str());

}

void ground::draw(Shader& area) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_ground);
    for (int i = -5; i < 13; i++)
    {
        for (int j = -13; j < 14; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 0.1f, float(j)));
            area.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -5; i < -1; i++)
    {
        for (int j = -13; j < -9; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.1f, float(j)));
            area.setMat4("model", amodel);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -1; i < 13; i++)
    {
        for (int j = -13; j < -11; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.1f, float(j)));
            area.setMat4("model", amodel);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -3; i < 13; i++)
    {
        for (int j = 11; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.1f, float(j)));
            area.setMat4("model", amodel);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -5; i < -3; i++)
    {
        for (int j = -13; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.1f, float(j)));
            area.setMat4("model", amodel);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = 11; i < 13; i++)
    {
        for (int j = -13; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.1f, float(j)));
            area.setMat4("model", amodel);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}
