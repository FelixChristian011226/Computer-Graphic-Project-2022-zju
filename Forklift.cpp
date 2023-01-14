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
#include "Transporter.h"
#include "Forklift.h"

unsigned int Forklift::texture_body = 0;
unsigned int Forklift::texture_cab = 0;
unsigned int Forklift::texture_fork = 0;
unsigned int Forklift::texture_tyre = 0;
unsigned int Forklift::texture_tyre2 = 0;
unsigned int Forklift::texture_frame = 0;
unsigned int Forklift::VAO[6] = { 0,0,0,0,0,0 };
unsigned int Forklift::VBO[6] = { 0,0,0,0,0,0 };

float body[] = {
    // positions          // normals           // texture coords
    -1.0f, -0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     1.0f, -0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     1.0f,  0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     1.0f,  0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -1.0f,  0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -1.0f, -0.4f, -0.8f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -1.0f, -0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     1.0f, -0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     1.0f,  0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     1.0f,  0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -1.0f,  0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -1.0f, -0.4f,  0.8f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -1.0f,  0.4f,  0.8f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -1.0f,  0.4f, -0.8f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -1.0f, -0.4f, -0.8f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -1.0f, -0.4f, -0.8f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -1.0f, -0.4f,  0.8f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -1.0f,  0.4f,  0.8f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     1.0f,  0.4f,  0.8f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     1.0f,  0.4f, -0.8f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     1.0f, -0.4f, -0.8f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     1.0f, -0.4f, -0.8f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     1.0f, -0.4f,  0.8f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     1.0f,  0.4f,  0.8f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -1.0f, -0.4f, -0.8f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     1.0f, -0.4f, -0.8f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     1.0f, -0.4f,  0.8f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     1.0f, -0.4f,  0.8f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -1.0f, -0.4f,  0.8f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -1.0f, -0.4f, -0.8f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -1.0f,  0.4f, -0.8f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     1.0f,  0.4f, -0.8f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     1.0f,  0.4f,  0.8f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     1.0f,  0.4f,  0.8f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -1.0f,  0.4f,  0.8f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -1.0f,  0.4f, -0.8f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float cab[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.8f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.8f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.8f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.8f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.8f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.8f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.8f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.8f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.8f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.8f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.8f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.8f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.8f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.8f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.8f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.8f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.8f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.8f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.8f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.8f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.8f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.8f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.8f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.8f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.8f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.8f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

float fork[] = {
    // positions          // normals
    -0.5f, -0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.5f, -0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.5f,  0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.5f,  0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f,  0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.05f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.05f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.05f,  0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.05f, -0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.05f, -0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.05f, -0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.05f,  0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.05f,  0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

     0.5f,  0.05f,  0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.05f, -0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.05f, -0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.05f, -0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.05f,  0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.5f,  0.05f,  0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.5f, -0.05f, -0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.05f, -0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.05f,  0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.05f,  0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.05f,  0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.05f, -0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.05f, -0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.05f, -0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.05f,  0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.05f,  0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.05f,  0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.05f, -0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

float frame[] = {
    // positions          // normals
    -0.05f, -0.5f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.05f, -0.5f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.05f,  1.7f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.05f,  1.7f, -0.1f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.05f,  1.7f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.05f, -0.5f, -0.1f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.05f, -0.5f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
     0.05f, -0.5f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
     0.05f,  1.7f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
     0.05f,  1.7f,  0.1f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.05f,  1.7f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    -0.05f, -0.5f,  0.1f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

    -0.05f,  1.7f,  0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.05f,  1.7f, -0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.05f, -0.5f, -0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.05f, -0.5f, -0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.05f, -0.5f,  0.1f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.05f,  1.7f,  0.1f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

     0.05f,  1.7f,  0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
     0.05f,  1.7f, -0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
     0.05f, -0.5f, -0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.05f, -0.5f, -0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
     0.05f, -0.5f,  0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
     0.05f,  1.7f,  0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.05f, -0.5f, -0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.05f, -0.5f, -0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.05f, -0.5f,  0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.05f, -0.5f,  0.1f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.05f, -0.5f,  0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.05f, -0.5f, -0.1f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.05f,  1.7f, -0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.05f,  1.7f, -0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.05f,  1.7f,  0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.05f,  1.7f,  0.1f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.05f,  1.7f,  0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.05f,  1.7f, -0.1f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

std::vector<float> tyre;

std::vector<float> tyre2;

Forklift::Forklift(float x, float z, int front) {
    type = object_type::FORKLIFT;
    index = current_index;
    current_index++;
    Position = glm::vec3(x, 1.85 + GROUND, z);
    Front = front;
    fork_y = 0.0;
    tyre_angle = 0.0;
    box = NULL;
    objects[index] = this;
    float* f = new float[4];
    if (front == 0) {
        f[0] = x - 1.0;
        f[1] = x + 2.1;
        f[2] = z - 0.8;
        f[3] = z + 0.8;
    }
    else if (front == 90) {
        f[0] = x - 0.8;
        f[1] = x + 0.8;
        f[2] = z - 2.1;
        f[3] = z + 1.0;
    }
    else if (front == 180) {
        f[0] = x - 2.1;
        f[1] = x + 1.0;
        f[2] = z - 0.8;
        f[3] = z + 0.8;
    }
    else if (front == 270) {
        f[0] = x - 0.8;
        f[1] = x + 0.8;
        f[2] = z - 1.0;
        f[3] = z + 2.1;
    }
    else {
        std::cout << ">illegal angle<\n";
        exit(1);
    }
    territory[index] = f;
}

void Forklift::forward(float v) { 
    if (Front == 0) {
        Position += glm::vec3(v, 0.0, 0.0);
    }
    else if (Front == 90) {
        Position += glm::vec3(0.0, 0.0, -v);
    }
    else if (Front == 180) {
        Position += glm::vec3(-v, 0.0, 0.0);
    }
    else if (Front == 270) {
        Position += glm::vec3(0.0, 0.0, v);
    }
    else {
        std::cout << "\n>>>>>forward::Illegal angle<<<<<\n";
        //exit(1);
    }
    if (Front == 0) {
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 2.1;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 1.0;
    }
    else if (Front == 90) {
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 2.1;
        territory[index][3] = Position.z + 1.0;
    }
    else if (Front == 180) {
        territory[index][0] = Position.x - 2.1;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 1.0;
    }
    else if (Front == 270) {
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 2.1;
    }
}

bool Forklift::forward(float x, float deltaTime) {
    static bool finish = true;
    static float distance;
    if (finish == true) distance = x;
    float v = deltaTime * CAR_SPEED;
    tyre_angle += deltaTime * ANGULAR_SPEED;
    while (tyre_angle >= 360) {
        tyre_angle -= 360;
    }
    if (distance > v) {
        forward(v);
        distance -= v;
        finish = false;
    }
    else {
        forward(distance);
        distance = 0;
        finish = true;
    }
    return finish;
}

bool Forklift::backward(float x, float deltaTime) {
    static bool finish = true;
    static float distance;
    if (finish == true) distance = x;
    float v = deltaTime * CAR_SPEED;
    tyre_angle -= deltaTime * ANGULAR_SPEED;
    while (tyre_angle >= 360) {
        tyre_angle -= 360;
    }
    if (distance > v) {
        forward(-v);
        distance -= v;
        finish = false;
    }
    else {
        forward(-distance);
        distance = 0;
        finish = true;
    }
    return finish;
}
bool Forklift::rotate(bool left) {
    int next_angle;
    if (left) {
        Front += 1;
        if (Front >= 360) Front -= 360;
        if (Front > 0 && Front <= 90) next_angle = 90;
        else if (Front > 90 && Front <= 180) next_angle = 180;
        else if (Front > 180 && Front <= 270) next_angle = 270;
        else next_angle = 0;
    }
    else {
        Front -= 1;
        if (Front < 0) Front += 360;
        if (Front >= 0 && Front < 90) next_angle = 0;
        else if (Front >= 90 && Front < 180) next_angle = 90;
        else if (Front >= 180 && Front < 270) next_angle = 180;
        else next_angle = 270;
    }
    switch (next_angle) {
    case 0:
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 2.1;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 1.0;
        break;
    case 90:
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 2.1;
        territory[index][3] = Position.z + 1.0;
        break;
    case 180:
        territory[index][0] = Position.x - 2.1;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 1.0;
        break;
    case 270:
        territory[index][0] = Position.x - 1.0;
        territory[index][1] = Position.x + 1.0;
        territory[index][2] = Position.z - 1.0;
        territory[index][3] = Position.z + 2.1;
        break;
    }
    if (Front == 0 || Front == 90 || Front == 180 || Front == 270) return true;
    else return false;
}



void Forklift::initial() {
    texture_fork = loadTexture("pic/fork.jpg");
    texture_body = loadTexture("pic/body.jpg");
    texture_cab = loadTexture("pic/cab.jpg");
    texture_tyre = loadTexture("pic/tyre.jpg");
    texture_tyre2 = loadTexture("pic/tyre2.jpg");
    texture_frame = loadTexture("pic/frame.png");

    int delta = 360 / C_STRIP;
    float alpha = 0;
    float x1 = 0.0, x2 = 0.0, y1 = TYRE_SIZE, y2 = TYRE_SIZE;
    
    for (int i = 0; i < C_STRIP; i++) {
        alpha += delta;
        x1 = x2;
        y1 = y2;
        y2 = cos(glm::radians(alpha)) * TYRE_SIZE;
        x2 = sin(glm::radians(alpha)) * TYRE_SIZE;
        tyre.push_back(x1); tyre.push_back(y1); tyre.push_back(0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(0); tyre.push_back(0);
        tyre.push_back(x2); tyre.push_back(y2); tyre.push_back(0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(1); tyre.push_back(0);
        tyre.push_back(x2); tyre.push_back(y2); tyre.push_back(-0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(1); tyre.push_back(1);
        tyre.push_back(x1); tyre.push_back(y1); tyre.push_back(0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(0); tyre.push_back(0);
        tyre.push_back(x2); tyre.push_back(y2); tyre.push_back(-0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(1); tyre.push_back(1);
        tyre.push_back(x1); tyre.push_back(y1); tyre.push_back(-0.1); tyre.push_back((x1 + x2) / 2); tyre.push_back((y1 + y2) / 2); tyre.push_back(0); tyre.push_back(0); tyre.push_back(1);
        
        tyre2.push_back(x1); tyre2.push_back(y1); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(1); tyre2.push_back(0.5 + x1); tyre2.push_back(0.5 + y1);
        tyre2.push_back(x2); tyre2.push_back(y2); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(1); tyre2.push_back(0.5 + x2); tyre2.push_back(0.5 + y2);
        tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(0); tyre2.push_back(1); tyre2.push_back(0.5); tyre2.push_back(0.5);
        
    }
    
    glGenVertexArrays(6, VAO);
    glGenBuffers(6, VBO);

    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fork), fork, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(body), body, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cab), cab, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, tyre.size() * sizeof(float), &tyre[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, tyre2.size() * sizeof(float), &tyre2[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frame), frame, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Forklift::draw(Shader& shader) {
    shader.use();
    shader.setInt("material.diffuse", 0);
    shader.setInt("material.specular", 0);
    shader.setFloat("material.shininess", 32.0f);
    glm::mat4 base_tran(1.0f);
    glm::mat4 model(1.0f);
    float angle = Front;
    base_tran = glm::translate(base_tran, Position);
    base_tran = glm::rotate<float>(base_tran, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0)); 
    shader.setMat4("model", base_tran);
    //cab
    glBindVertexArray(VAO[2]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_cab);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glBindTexture(GL_TEXTURE_2D, texture_body);
    glDrawArrays(GL_TRIANGLES, 30, 36);
    
    //body
    model = glm::translate(base_tran, glm::vec3(0.0, -1.2, 0.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[1]);
    glBindTexture(GL_TEXTURE_2D, texture_body);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //fork
    model = glm::translate(base_tran, glm::vec3(1.6, -1.45 + fork_y, 0.4));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[0]);
    glBindTexture(GL_TEXTURE_2D, texture_fork);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::translate(base_tran, glm::vec3(1.6, -1.45 + fork_y, -0.4));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[0]);
    glBindTexture(GL_TEXTURE_2D, texture_fork);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    if (box) {
        box->SetPos(Position.x + cos(glm::radians(float(Front))) * 1.6, -1.0 + fork_y + Position.y, Position.z - sin(glm::radians(float(Front))) * 1.6);
        ((Container*)box)->SetAng(Front);
    }

    //frame
    model = glm::translate(base_tran, glm::vec3(1.05, -1.0, 0.4));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[5]);
    glBindTexture(GL_TEXTURE_2D, texture_frame);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    model = glm::translate(base_tran, glm::vec3(1.05, -1.0, -0.4));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[5]);
    glBindTexture(GL_TEXTURE_2D, texture_frame);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //tyre
    model = glm::translate(base_tran, glm::vec3(0.5, -1.45, 0.9));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, -1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[3]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 6);

    model = glm::translate(base_tran, glm::vec3(0.5, -1.45, 1.0));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, -1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[4]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre2);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 3);

    model = glm::translate(base_tran, glm::vec3(-0.5, -1.45, 0.9));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[3]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 6);

    model = glm::translate(base_tran, glm::vec3(-0.5, -1.45, 1.0));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, -1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[4]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre2);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 3);

    model = glm::translate(base_tran, glm::vec3(-0.5, -1.45, -0.9));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, -1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[3]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 6);

    model = glm::translate(base_tran, glm::vec3(-0.5, -1.45, -1.0));
    model = glm::rotate<float>(model, glm::radians(180.0), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[4]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre2);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 3);

    model = glm::translate(base_tran, glm::vec3(0.5, -1.45, -0.9));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, -1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[3]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 6);

    model = glm::translate(base_tran, glm::vec3(0.5, -1.45, -1.0));
    model = glm::rotate<float>(model, glm::radians(180.0), glm::vec3(0.0, 1.0, 0.0));
    model = glm::rotate<float>(model, glm::radians(tyre_angle), glm::vec3(0.0, 0.0, 1.0));
    shader.setMat4("model", model);
    glBindVertexArray(VAO[4]);
    glBindTexture(GL_TEXTURE_2D, texture_tyre2);
    glDrawArrays(GL_TRIANGLES, 0, C_STRIP * 3);

    glBindVertexArray(0);

    
}

bool Forklift::rise(int x, float deltaTime) {
    float v = deltaTime * CAR_SPEED * 0.1;
    if (x > 2) x = 2;
    fork_y += v;
    if (fork_y >= x) {
        fork_y = x;
        return true;
    }
    else return false;
}

bool Forklift::decline(float deltaTime) {
    float v = deltaTime * CAR_SPEED * 0.1;
    fork_y -= v;
    if (fork_y <= 0) {
        fork_y = 0;
        return true;
    }
    else return false;
}

bool Forklift::getbox(Object* container) {
    if (box != NULL) {
        std::cout << ">The forklift has a box already<\n";
        return false;
    }
    if (fork_y != 0) {
        std::cout << ">The fork has not been lowered<\n";
    }
    bool available = false;
    glm::vec3 box_pos = container->getPos();
    if (Front == 0 && box_pos.x > Position.x && box_pos.x - Position.x <= 3.0 && abs(box_pos.z - Position.z) <= 0.5) available = true;
    else if (Front == 90 && box_pos.z < Position.z && Position.z - box_pos.z <= 3.0 && abs(box_pos.x - Position.x) <= 0.5) available = true;
    else if (Front == 180 && box_pos.x < Position.x && Position.x - box_pos.x <= 3.0 && abs(box_pos.z - Position.z) <= 0.5) available = true;
    else if (Front == 270 && box_pos.z > Position.z && box_pos.z - Position.z <= 3.0 && abs(box_pos.x - Position.x) <= 0.5) available = true;
    else if (Front != 0 && Front != 90 && Front != 180 && Front != 270) {
        std::cout << "\n>>>>>getbox::Illegal angle<<<<<\n";
        exit(1);
    }
    if (available) {
        box = container;
        ((Container*)box)->resetShelf();
        box->SetPos(cos(glm::radians(float(Front))) * 1.6, -1.0 + fork_y, -sin(glm::radians(float(Front))) * 1.6);
        return true;
    }
    std::cout << ">The box is too far<\n";
    return false;
}

bool Forklift::dropbox() {
    if (box == NULL) {
        std::cout << ">The box has not been loaded<\n";
        return false;
    }
    else if (fork_y != 0.0) {
        std::cout << ">The fork has not been lowered<\n";
        return false;
    }
    else {
        box = NULL;
        return true;
    }
}

bool Forklift::storebox(Object* depend) {
    bool pos_x, neg_x, pos_z, neg_z;
    pos_x = (Front == 0 && depend->getPos().x - Position.x < 4.5 && depend->getPos().x > Position.x);
    neg_x = (Front == 180 && depend->getPos().x < Position.x&& Position.x - depend->getPos().x < 4.5);
    pos_z = (Front == 270 && depend->getPos().z - Position.z < 4.5 && depend->getPos().z > Position.z);
    neg_z = (Front == 90 && depend->getPos().z < Position.z&& Position.z - depend->getPos().z < 4.5);
    if (depend->GetType() == object_type::SHELF) {
        if (((Shelf*)depend)->get_front() && (pos_x || neg_x)) {
            int i;
            for (i = 0; i < ((Shelf*)depend)->get_length(); i++) {
                if (depend->getPos().z - i - Position.z <= 0.5 || Position.z - depend->getPos().z + i >= 0.5) break;
            }
            if (i == ((Shelf*)depend)->get_length()) {
                std::cout << ">shelf is too far, i out of range<\n";
                return false;
            }
            else {
                if (fork_y < 0.6 && ((Shelf*)depend)->loadbox(1, i)) {
                    box->SetPos(depend->getPos() + glm::vec3(0.0, -0.5, -i));
                    ((Container*)box)->setShelf(depend, 1, i);
                    box = NULL;
                    return true;
                }
                else if (fork_y >= 0.6 && ((Shelf*)depend)->loadbox(0, i)) {
                    box->SetPos(depend->getPos() + glm::vec3(0.0, 0.5, -i));
                    ((Container*)box)->setShelf(depend, 0, i);
                    box = NULL;
                    return true;
                }
                else {
                    std::cout << ">the shelf has been loaded<\n";
                    return false;
                }
            }
        }
        else if (!((Shelf*)depend)->get_front() && (pos_z || neg_z)) {
            int i = 0;
            for (int i = 0; i < ((Shelf*)depend)->get_length(); i++) {
                if (depend->getPos().x + i - Position.x <= 0.5 || Position.x - depend->getPos().x - i <= 0.5) break;
            }
            if (i == ((Shelf*)depend)->get_length()) {
                std::cout << ">shelf is too far<\n";
                return false;
            }
            else {
                if (fork_y < 0.6 && ((Shelf*)depend)->loadbox(1, i)) {
                    box->SetPos(depend->getPos() + glm::vec3(i, -0.5, 0.0));
                    ((Container*)box)->setShelf(depend, 1, i);
                    box = NULL;
                    return true;
                }
                else if (fork_y >= 0.6 && ((Shelf*)depend)->loadbox(0, i)) {
                    box->SetPos(depend->getPos() + glm::vec3(i, 0.5, 0.0));
                    ((Container*)box)->setShelf(depend, 0, i);
                    box = NULL;
                    return true;
                }
                else {
                    std::cout << ">the shelf has been loaded<\n";
                    return false;
                }
            }
        }
        else {
            std::cout << ">>shelf is too far<<\n";
            return false;
        }
    }
    else if (depend->GetType() == object_type::TRANSPORTER) {
        float* f = territory[depend->GetIndex()];
        glm::vec3 Pos = box->getPos();
        if ((pos_x || neg_x) && Position.z > f[2] && Position.z < f[3]) {
            Pos = glm::vec3(depend->getPos().x, depend->getPos().y + 0.5, Pos.z);
        }
        else if ((pos_z || neg_z) && Position.x > f[0] && Position.x < f[1]) {
            Pos = glm::vec3(Pos.x, depend->getPos().y + 0.5, depend->getPos().z);
        }
        else {
            std::cout << ">transporter is too far<\n";
            return false;
        }
        ((Transporter*)depend)->getbox(box);
        box->SetPos(Pos);
        box = NULL;
        return true;
    }
    else {
        std::cout << ">object with type {" << depend->GetType() << "} couldn't load box\n<";
        return false;
    }
}