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
#include "lift.h"

elift::elift(const std::string inputpic, const float vertices[]) {
    this->face = inputpic;
    for (int i = 0; i < LIFTSIZE; i++) this->liftVertices[i] = vertices[i];
}
void elift::initial() {
    glGenVertexArrays(1, &lVAO);
    glGenBuffers(1, &lVBO);
    glBindVertexArray(lVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(liftVertices), liftVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->texture_lift = loadTexture(face.c_str());

}

float elift::draw(float x, float y, float z, Shader& lift, int& upflag, int& protect1,
    int& uprotect1, float& locy, int& protect3, int& floor1,
    int& openflag, int& protect2, int& uprotect, int& in_it,
    float& loc1, int& protect, float& loc, int& openflag1,
    glm::vec3 camera) {
    
    if (upflag) {
        protect1 = 1;
        uprotect1 = 1;
        if (locy < 4.0 && upflag == 1) {
            protect3 = 1;
            locy += 0.01;
            if (inlift(camera)) {
                floor1 = 0;
            }
        }
        else if (locy >= 4.0 && upflag == 1) {
            protect3 = 0;
            uprotect1 = 0;
            if (inlift(camera)) {
                floor1 = 2;
            }
        }
        else if (locy > 0.0 && upflag == 2) {
            locy -= 0.01;
            protect3 = 1;
            if (inlift(camera)) {
                floor1 = 0;
            }
        }
        else if (upflag == 2 && locy <= 0.0) {
            upflag = 0;
            protect3 = 0;
            protect1 = 0;
            if (inlift(camera)) {
                floor1 = 1;
            }
        }
    }
    if (openflag == 0);
    else {
        protect2 = 1;
        if (loc < 1.0 && openflag == 1) {
            protect = 1;
            loc += 0.01;
            in_it = 0;
        }
        else if (loc >= 1.0 && openflag == 1) {
            protect = 0;
            in_it = 0;
        }
        else if (loc > 0.0 && openflag == 2) {
            in_it = 0;
            loc -= 0.01;
            protect = 1;
        }
        else if (openflag == 2 && loc <= 0.0) {
            if (inlift(camera)) {
                in_it = 1;
            }
            else in_it = 0;
            openflag = 0;
            protect = 0;
            protect2 = 0;
        }
    }
    if (openflag1) {
        protect2 = 1;
        if (loc1 < 1.0 && openflag1 == 1) {
            uprotect = 1;
            loc1 += 0.01;
            in_it = 0;
        }
        else if (loc1 >= 1.0 && openflag1 == 1) {
            uprotect = 0;
            in_it = 0;
        }
        else if (loc1 > 0.0 && openflag1 == 2) {
            loc1 -= 0.01;
            uprotect = 1;
            in_it = 0;
        }
        else if (openflag1 == 2 && loc1 <= 0.0) {
            if (inlift(camera)) {
                in_it = 1;
            }
            else in_it = 0;
            openflag1 = 0;
            uprotect = 0;
            protect2 = 0;
        }
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture_lift);
    lift.use();
    glBindVertexArray(lVAO);
    glm::mat4 emodel = glm::mat4(1.0f);
    emodel = glm::translate(emodel, glm::vec3(x + loc, y, z + 0.01));
    emodel = glm::rotate(emodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", emodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 emodel1 = glm::mat4(1.0f);
    emodel1 = glm::translate(emodel1, glm::vec3(x - 1 - loc, y, z + 0.01));
    emodel1 = glm::rotate(emodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", emodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 emodel22 = glm::mat4(1.0f);
    emodel22 = glm::translate(emodel22, glm::vec3(x + loc, y+1, z + 0.01));
    emodel22 = glm::rotate(emodel22, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", emodel22);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 emodel12 = glm::mat4(1.0f);
    emodel12 = glm::translate(emodel12, glm::vec3(x - 1 - loc, y+1, z + 0.01));
    emodel12 = glm::rotate(emodel12, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", emodel12);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //second floor movable
    glm::mat4 semodel = glm::mat4(1.0f);
    semodel = glm::translate(semodel, glm::vec3(x + loc1, y + 4, z + 0.01));
    semodel = glm::rotate(semodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", semodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 semodel1 = glm::mat4(1.0f);
    semodel1 = glm::translate(semodel1, glm::vec3(x - 1 - loc1, y + 4, z + 0.01));
    semodel1 = glm::rotate(semodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", semodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    semodel = glm::mat4(1.0f);
    semodel = glm::translate(semodel, glm::vec3(x + loc1, y + 5, z + 0.01));
    semodel = glm::rotate(semodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", semodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    semodel1 = glm::mat4(1.0f);
    semodel1 = glm::translate(semodel1, glm::vec3(x - 1 - loc1, y + 5, z + 0.01));
    semodel1 = glm::rotate(semodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", semodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    //up
    glm::mat4 femodel = glm::mat4(1.0f);
    femodel = glm::translate(femodel, glm::vec3(x + 0.1, y + locy - 0.04, z + 0.89));
    femodel = glm::rotate(femodel, glm::radians(90.0f), glm::vec3(0, 0, 1));
    lift.setMat4("model", femodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 femodel1 = glm::mat4(1.0f);
    femodel1 = glm::translate(femodel1, glm::vec3(x - 0.9, y + locy - 0.04, z + 0.89));
    femodel1 = glm::rotate(femodel1, glm::radians(90.0f), glm::vec3(0, 0, 1));
    lift.setMat4("model", femodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //bottom
    glm::mat4 boemodel = glm::mat4(1.0f);
    boemodel = glm::translate(boemodel, glm::vec3(x + 0.1, y + locy + 2.0, z + 0.89));
    boemodel = glm::rotate(boemodel, glm::radians(90.0f), glm::vec3(0, 0, 1));
    lift.setMat4("model", boemodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 boemodel1 = glm::mat4(1.0f);
    boemodel1 = glm::translate(boemodel1, glm::vec3(x - 0.9, y + locy + 2.0, z + 0.89));
    boemodel1 = glm::rotate(boemodel1, glm::radians(90.0f), glm::vec3(0, 0, 1));
    lift.setMat4("model", boemodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm::mat4 uemodel = glm::mat4(1.0f);
    uemodel = glm::translate(uemodel, glm::vec3(x + (openflag1 ? loc1 : loc), y + locy, z + 0.02));
    uemodel = glm::rotate(uemodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", uemodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 uemodel1 = glm::mat4(1.0f);
    uemodel1 = glm::translate(uemodel1, glm::vec3(x - 1 - (openflag1 ? loc1 : loc), y + locy, z + 0.02));
    uemodel1 = glm::rotate(uemodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", uemodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    uemodel = glm::mat4(1.0f);
    uemodel = glm::translate(uemodel, glm::vec3(x + (openflag1 ? loc1 : loc), y + locy+1, z + 0.02));
    uemodel = glm::rotate(uemodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", uemodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    uemodel1 = glm::mat4(1.0f);
    uemodel1 = glm::translate(uemodel1, glm::vec3(x - 1 - (openflag1 ? loc1 : loc), y + locy+1, z + 0.02));
    uemodel1 = glm::rotate(uemodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", uemodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);



    glm::mat4 bemodel = glm::mat4(1.0f);
    bemodel = glm::translate(bemodel, glm::vec3(x, y + locy, z + 0.91));
    bemodel = glm::rotate(bemodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", bemodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 bemodel1 = glm::mat4(1.0f);
    bemodel1 = glm::translate(bemodel1, glm::vec3(x - 1, y + locy, z + 0.91));
    bemodel1 = glm::rotate(bemodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", bemodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    bemodel = glm::mat4(1.0f);
    bemodel = glm::translate(bemodel, glm::vec3(x, y + locy+1, z + 0.91));
    bemodel = glm::rotate(bemodel, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", bemodel);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    bemodel1 = glm::mat4(1.0f);
    bemodel1 = glm::translate(bemodel1, glm::vec3(x - 1, y + locy+1, z + 0.91));
    bemodel1 = glm::rotate(bemodel1, glm::radians(90.0f), glm::vec3(0, 1, 0));
    lift.setMat4("model", bemodel1);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    glm::mat4 emodel2 = glm::mat4(1.0f);
    emodel2 = glm::translate(emodel2, glm::vec3(x + 0.91, y + locy, z + 0.81));
    lift.setMat4("model", emodel2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glm::mat4 emodel3 = glm::mat4(1.0f);
    emodel3 = glm::translate(emodel3, glm::vec3(x - 1.21, y + locy, z + 0.81));
    lift.setMat4("model", emodel3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    emodel2 = glm::mat4(1.0f);
    emodel2 = glm::translate(emodel2, glm::vec3(x + 0.91, y + locy+1, z + 0.81));
    lift.setMat4("model", emodel2);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    emodel3 = glm::mat4(1.0f);
    emodel3 = glm::translate(emodel3, glm::vec3(x - 1.21, y + locy+1, z + 0.81));
    lift.setMat4("model", emodel3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    return locy;
}
int elift::inlift(glm::vec3 camera) {
    if (camera.x >= 9.05 && camera.x <= 10.95 && camera.z >= 12.55 && camera.z <= 13.45) {
        return 1;
    }
    return 0;
}