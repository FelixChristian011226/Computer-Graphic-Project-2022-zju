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
#include "roof.h"

roof::roof(const std::string inputpic, const float vertices[]) {
    this->face = inputpic;
    for (int i = 0; i < ROOFSIZE; i++) this->roofVertices[i] = vertices[i];
}
void roof::initial() {
    glGenVertexArrays(1, &rVAO);
    glGenBuffers(1, &rVBO);
    glBindVertexArray(rVAO);
    glBindBuffer(GL_ARRAY_BUFFER, rVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(roofVertices), roofVertices, GL_STATIC_DRAW);
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

    this->texture_roof = loadTexture(face.c_str());

}

void roof::draw(Shader& area_back) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_roof);
    glBindVertexArray(rVAO);

    for (int i = -13; i < 14; i++) {
        glm::mat4 bmodel = glm::mat4(1.0f);
        bmodel = glm::translate(bmodel, glm::vec3(-5.6f, 8.0, 1.0 * i));
        bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
        bmodel = glm::translate(bmodel, glm::vec3(0.0f, -3.6, 0.0));
        area_back.setMat4("model", bmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    for (int i = -13; i < 14; i++) {
        glm::mat4 bmodel = glm::mat4(1.0f);
        bmodel = glm::translate(bmodel, glm::vec3(-0.7f + 13, 8.0, 1.0 * i));
        bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
        bmodel = glm::translate(bmodel, glm::vec3(0.0f, -3.6, 0.0));
        area_back.setMat4("model", bmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 11; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(1.0f, 0.0, 0.0f));
            bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
            bmodel = glm::translate(bmodel, glm::vec3(-5.6 + 1.79 * j, 0.5, -8.2 - i));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 11; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::translate(bmodel, glm::vec3(0.0, 10.65, 0.0));
            bmodel = glm::rotate(bmodel, glm::radians(12.5f), glm::vec3(1.0f, 0.0, 0.0f));
            bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
            bmodel = glm::translate(bmodel, glm::vec3(-5.6 + 1.79 * j, 0.0, 0.5 + i));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 11; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::translate(bmodel, glm::vec3(0.0, 10.65, 0.0));
            bmodel = glm::rotate(bmodel, glm::radians(180.0f), glm::vec3(0.0f, 1.0, 0.0f));
            bmodel = glm::rotate(bmodel, glm::radians(12.5f), glm::vec3(1.0f, 0.0, 0.0f));
            bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
            bmodel = glm::translate(bmodel, glm::vec3(-11.6 + 1.79 * j, 0.0, 0.5 + i));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -5; i < 13; i++) {
        for (int j = 0; j < 28; j++) {
            glm::mat4 bmodel = glm::mat4(1.0f);
            bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
            bmodel = glm::translate(bmodel, glm::vec3(13.8f - j, 8.0, 1.0 * i - 0.5f));
            bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
            bmodel = glm::translate(bmodel, glm::vec3(0.0f, -3.6, 0.0));
            area_back.setMat4("model", bmodel);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    for (int i = -5; i < 13; i++) {
        glm::mat4 bmodel = glm::mat4(1.0f);
        bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        bmodel = glm::translate(bmodel, glm::vec3(13.8f - 13.5, 11.0, 1.0 * i - 0.5f));
        bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
        bmodel = glm::translate(bmodel, glm::vec3(0.0f, -3.6, 0.0));
        area_back.setMat4("model", bmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    for (int i = -5; i < 13; i++) {
        glm::mat4 bmodel = glm::mat4(1.0f);
        bmodel = glm::rotate(bmodel, glm::radians(90.0f), glm::vec3(0.0f, 1.0, 0.0f));
        bmodel = glm::translate(bmodel, glm::vec3(13.8f - 13.5, 8.0, 1.0 * i - 0.5f));
        bmodel = glm::scale(bmodel, glm::vec3(1.0, 0.1, 1.0));
        bmodel = glm::translate(bmodel, glm::vec3(0.0f, -3.6, 0.0));
        area_back.setMat4("model", bmodel);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
