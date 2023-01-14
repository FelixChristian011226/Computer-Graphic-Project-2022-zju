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
#include "wall.h"


wall::wall(const std::string inputpic, const float vertices[]) {
    this->face = inputpic;
    for (int i = 0; i < WALLSIZE; i++) this->wallVertices[i] = vertices[i];
}
void wall::initial() {
    glGenVertexArrays(1, &wVAO);
    glGenBuffers(1, &wVBO);
    glBindVertexArray(wVAO);
    glBindBuffer(GL_ARRAY_BUFFER, wVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertices), wallVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    unsigned int btexture1;
    glGenTextures(1, &btexture1);
    glBindTexture(GL_TEXTURE_2D, btexture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    this->texture_wall = loadTexture(face.c_str());

}

void wall::draw(Shader& area_back) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_wall);
    glBindVertexArray(wVAO);
    
    for (int i = -13; i < 14; i++) {
        for (int j = 0; j < 8; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::translate(bmodel, glm::vec3(-5.6f, 1.0 * j, 1.0 * i));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -13; i < 14; i++) {
        for (int j = 0; j < 8; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::translate(bmodel, glm::vec3(-0.7f + 13, 1.0 * j, 1.0 * i));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -5; i < 13; i++) {
        for (int j = 0; j < 8; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
            bmodel = glm::translate(bmodel, glm::vec3(13.8f, 1.0 * j, 1.0 * i - 0.5f));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -5; i < 13; i++) {
        for (int j = 0; j < 8; j++) {
            if (((j == 0||j==1) && (i == 10 || i == 11)) || ((j == 4||j==5) && (i == 10 || i == 11))) continue;
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
            bmodel = glm::translate(bmodel, glm::vec3(0.8f - 13, 1.0 * j, 1.0 * i - 0.5f));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -5; i < 13; i++) {
        for (int j = 0; j < 8; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
            bmodel = glm::translate(bmodel, glm::vec3(0.8f - 14, 1.0 * j, 1.0 * i - 0.5f));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }

}
