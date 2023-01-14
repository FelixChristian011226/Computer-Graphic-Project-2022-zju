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
#include "floors.h"


floors::floors(const std::string inputpic, const float vertices[], const int indices[]) {
    this->face = inputpic;
    for (int i = 0; i < FLOORVSIZE; i++) this->floorVertices[i] = vertices[i];
    for (int i = 0; i < FLOORISIZE; i++) this->floorIndices[i] = indices[i];
}
void floors::initial() {
    glGenVertexArrays(1, &fVAO);
    glGenBuffers(1, &fVBO);
    glGenBuffers(1, &this->fEB0);
    glBindVertexArray(fVAO);
    glBindBuffer(GL_ARRAY_BUFFER, fVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->fEB0);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorIndices), floorIndices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unsigned int textureb;
    glGenTextures(1, &textureb);
    glBindTexture(GL_TEXTURE_2D, textureb);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->texture_floor = loadTexture(face.c_str());

}

void floors::draw(Shader& area_back) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_floor);
    for (int i = -5; i < -1; i++)
    {
        for (int j = -13; j < -9; j++) {
            glm::mat4 amodel(1.0f);
            glm::vec3(1.5 + 4 * j, 4.09, 2.0 + 4 * i);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.09f, float(j)));
            area_back.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -3; i < 13; i++)
    {
        for (unsigned int j = 11; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            glm::vec3(1.5 + 4 * j, 4.09, 2.0 + 4 * i);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.09f, float(j)));
            area_back.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -5; i < -3; i++)
    {
        for (int j = -13; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            glm::vec3(1.5 + 4 * j, 4.09, 2.0 + 4 * i);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.09f, float(j)));
            area_back.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = 11; i < 13; i++)
    {
        for (int j = -13; j < 13; j++) {
            glm::mat4 amodel(1.0f);
            glm::vec3(1.5 + 4 * j, 4.09, 2.0 + 4 * i);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.09f, float(j)));
            area_back.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
    for (int i = -1; i < 13; i++)
    {
        for (int j = -13; j < -11; j++) {
            glm::mat4 amodel(1.0f);
            glm::vec3(1.5 + 4 * j, 4.09, 2.0 + 4 * i);
            amodel = glm::translate(amodel, glm::vec3((float)(i)-0.5, 4.09f, float(j)));
            area_back.setMat4("model", amodel);
            glBindVertexArray(fVAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}
