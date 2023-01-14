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
#include "Transporter.h"

unsigned int Transporter::VAO[2] = { 0,0 };
unsigned int Transporter::VBO[2] = { 0,0 };
unsigned int Transporter::texture_tran1 = 0, Transporter::texture_tran2 = 0;
std::vector<float> rec;
std::vector<float> cub;

void Transporter::initial() {
    texture_tran1 = loadTexture("pic/tran.jpg");
    texture_tran2 = loadTexture("pic/tran2.jpg");

    int delta = 360 / T_STRIP;
    float alpha = 0;
    float x1 = 0.0, x2 = 0.0, y1 = RADIUS, y2 = RADIUS;

    for (int i = 0; i < T_STRIP; i++) {
        alpha += delta;
        x1 = x2;
        y1 = y2;
        y2 = cos(glm::radians(alpha)) * RADIUS;
        x2 = sin(glm::radians(alpha)) * RADIUS;
        rec.push_back(x1); rec.push_back(y1); rec.push_back(0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(0); rec.push_back(0);
        rec.push_back(x2); rec.push_back(y2); rec.push_back(0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(1); rec.push_back(0);
        rec.push_back(x2); rec.push_back(y2); rec.push_back(-0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(1); rec.push_back(1);
        rec.push_back(x1); rec.push_back(y1); rec.push_back(0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(0); rec.push_back(0);
        rec.push_back(x2); rec.push_back(y2); rec.push_back(-0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(1); rec.push_back(1);
        rec.push_back(x1); rec.push_back(y1); rec.push_back(-0.5); rec.push_back((x1 + x2) / 2); rec.push_back((y1 + y2) / 2); rec.push_back(0); rec.push_back(0); rec.push_back(1);
    }
    create_vertex(cub, 0.5, 0.1, 0.05);

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, rec.size() * sizeof(float), &rec[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, cub.size() * sizeof(float), &cub[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Transporter::Transporter(float x, float z, bool x_axis, int i_length) {
    Position = glm::vec3(x, 0.1 + GROUND, z);
    is_x_axis = x_axis;
    length = i_length;
    type = object_type::TRANSPORTER;
    index = current_index;
    current_index++;
    objects[index] = this;
    float* f = new float[4];
    territory[index] = f;
    if (is_x_axis) {
        f[0] = x - 0.5;
        f[1] = x - 0.5 + length;
        f[2] = z - 0.6;
        f[3] = z + 0.6;
    }
    else {
        f[0] = x - 0.6;
        f[1] = x + 0.6;
        f[2] = z + 0.5 - length;
        f[3] = z + 0.5;
    }
    tran_angle = 0;
}

int Transporter::GetLen() {
    return length;
}

void Transporter::draw(Shader& shader) {
    glm::mat4 model(1.0f);
    glm::mat4 bare_tran(1.0f);
    bare_tran = glm::translate(bare_tran, Position);
    if (!is_x_axis) bare_tran = glm::rotate<float>(bare_tran, glm::radians(90.0), glm::vec3(0.0, 1.0, 0.0));
    shader.use();
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 0);
    shader.setFloat("material.shiness", 32.0);
    glActiveTexture(GL_TEXTURE0);
    for (int i = 0; i < length; i++) {

        glBindTexture(GL_TEXTURE_2D, texture_tran2);
        glBindVertexArray(VAO[1]);
        model = glm::translate(bare_tran, glm::vec3(0.0, 0.0, 0.55));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::translate(bare_tran, glm::vec3(0.0, 0.0, -0.55));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(VAO[0]);
        glBindTexture(GL_TEXTURE_2D, texture_tran1);
        for (int j = 0; j < 0.5 / RADIUS; j++) {
            model = glm::translate(bare_tran, glm::vec3(-0.4 + 2 * RADIUS * j, 0.0, 0.0));
            model = glm::rotate(model, tran_angle, glm::vec3(0.0, 0.0, -1.0));
            shader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 6 * T_STRIP);
        }

        bare_tran = glm::translate(bare_tran, glm::vec3(1.0, 0.0, 0.0));
    }
}

void Transporter::rotate(float deltatime) {
    tran_angle += deltatime * 2;
    while (tran_angle >= 360) {
        tran_angle -= 360;
    }
    for (auto i = boxes.begin(); i != boxes.end();) {
        Object* box = (*i);
        glm::vec3 Pos = box->getPos();
        if (is_x_axis) {
            Pos.x += deltatime * 3.14159;
            if (Pos.x > territory[index][1] && Pos.y > GROUND + 0.4) {
                Pos = glm::vec3(Pos.x, Pos.y - 0.011, Pos.z);
                i++;
            }
            else if (Pos.x > territory[index][1] && Pos.y <= GROUND + 0.4) {
                Pos = glm::vec3(Pos.x, GROUND + 0.4, Pos.z);
                i = boxes.erase(i);
            }
            else {
                i++;
            }
        }
        else {
            Pos.z -= deltatime * 3.14159;
            if (Pos.z < territory[index][2] && Pos.y > GROUND + 0.4) {
                Pos = glm::vec3(Pos.x, Pos.y - 0.011, Pos.z);
                i++;
            }
            else if (Pos.z < territory[index][2] && Pos.y <= GROUND + 0.4) {
                Pos = glm::vec3(Pos.x, GROUND + 0.4, Pos.z);
                i = boxes.erase(i);
            }
            else {
                i++;
            }
        }
        box->SetPos(Pos);
    }
}

bool Transporter::getbox(Object* Container) {
    boxes.push_back(Container);
    return true;
}

bool Transporter::get_front() {
    return is_x_axis;
}

void Transporter::rotate() {
    is_x_axis = !is_x_axis;
    float* f = territory[index];
    if (is_x_axis) {
        f[0] = Position.x - 0.5;
        f[1] = Position.x - 0.5 + length;
        f[2] = Position.z - 0.6;
        f[3] = Position.z + 0.6;
    }
    else {
        f[0] = Position.x - 0.6;
        f[1] = Position.x + 0.6;
        f[2] = Position.z + 0.5 - length;
        f[3] = Position.z + 0.5;
    }
}