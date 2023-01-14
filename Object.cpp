#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include "Shader.h"
#include "Object.h"

int Object::current_index = 0;
int Object::selected = -1;
std::map<int, Object*> Object::objects;
std::map<int, float*> Object::territory;
unsigned int Object::VAO = 0;
unsigned int Object::VBO = 0;
unsigned int Object::EBO = 0;
unsigned int Object::indices[24] = {
	0, 1,
	2, 3,
	4, 5,
	6, 7,
	0, 6,
	2, 4,
	1, 7,
	3, 5,
	0, 2,
	1, 3,
	4, 6,
	5, 7
};

glm::vec3 Object::getPos() {
	return Position;
}

void Object::SetPos(glm::vec3 Pos) {
	float dif_x = Pos.x - Position.x;
	float dif_z = Pos.z - Position.z;
	Position = Pos;
	territory[index][0] += dif_x;
	territory[index][1] += dif_x;
	territory[index][2] += dif_z;
	territory[index][3] += dif_z;
}

void Object::SetPos(float x, float y, float z) {
	glm::vec3 Pos = glm::vec3(x, y, z);
	SetPos(Pos);
}
object_type Object::GetType() {
	return type;
}

void Object::SetType(object_type i_type) {
	type = i_type;
}

void Object::select(int index) {
	selected = index;
}

void Object::init_line() {
	glLineWidth(20);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Object::DrawFrame(Shader& shader) {
	if (selected == -1 || selected >= current_index) {
		return;
	}
	else {
		float* xz;
		xz = territory[selected];
		float y_min, y_max;
		switch (objects[selected]->type) {
		case object_type::CONTAINER: {
			y_max = objects[selected]->Position.y + 0.4;
			y_min = objects[selected]->Position.y - 0.4;
			break;
		}
		case object_type::FORKLIFT: {
			y_max = GROUND + 2.65;
			y_min = GROUND;
			break;
		}
		case object_type::SHELF: {
			y_max = GROUND + 2.0;
			y_min = GROUND;
			break;
		}
		case object_type::TRANSPORTER: {
			y_max = GROUND + 0.2;
			y_min = GROUND;
			break;
		}
		case object_type::CONSOLE: {
			y_max = GROUND + 1.0;
			y_min = GROUND;
		}
		case object_type::RAILING: {
			return;
		}
		}
		float vertices[] = {
			xz[0], y_min, xz[2],
			xz[0], y_max, xz[2],
			xz[1], y_min, xz[2],
			xz[1], y_max, xz[2],
			xz[1], y_min, xz[3],
			xz[1], y_max, xz[3],
			xz[0], y_min, xz[3],
			xz[0], y_max, xz[3]
		};
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		shader.use();
		glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
	}
}

int Object::GetIndex() {
	return index;
}