#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <map>
#include "load_texture.h"
#include "Shader.h"
#include "Object.h"
#include "shelf.h"

unsigned int Shelf::VAO[3] = { 0,0,0 };
unsigned int Shelf::VBO[3] = { 0,0,0 };
unsigned int Shelf::texture_shelf = 0;

std::vector<float> one;
std::vector<float> two;
std::vector<float> three;

Shelf::Shelf(int x, int z, bool x_axis, int Length) {
	type = object_type::SHELF;
	Position = glm::vec3(x, 1.0 + GROUND, z);
	is_x_axis = x_axis;
	length = Length;
	is_loaded[0] = new bool[length];
	is_loaded[1] = new bool[length];
	for (int i = 0; i < length; i++) {
		is_loaded[0][i] = false;
		is_loaded[1][i] = false;
	}
	index = current_index;
	current_index++;
	objects[index] = (this);
	float* f = new float[4];
	if (x_axis) {
		f[0] = x - 0.5;
		f[1] = x + 0.5;
		f[2] = z - length * 1.0 + 0.5;
		f[3] = z + 0.5;
	}
	else {
		f[0] = x - 0.5;
		f[1] = x + length * 1.0 - 0.5;
		f[2] = z - 0.5;
		f[3] = z + 0.5;
	}
	territory[index] = f;
}

void Shelf::initial() {

	create_vertex(one, 0.5, 0.05, 0.5);
	create_vertex(two, 0.05, 0.9, 0.5);
	create_vertex(three, 0.4, 0.1, 0.5);

	texture_shelf = loadTexture("pic/shelf.jpg");
	glGenVertexArrays(3, VAO);
	glGenBuffers(3, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, one.size() * sizeof(float), &one[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, two.size() * sizeof(float), &two[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, three.size() * sizeof(float), &three[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

bool Shelf::get_front() {
	if (is_x_axis) return true;
	else return false;
}

void Shelf::draw(Shader& shader) {
	glm::mat4 model(1.0f);
	glm::mat4 bare_tran(1.0f);
	bare_tran = glm::translate(bare_tran, Position);
	if(is_x_axis) bare_tran = glm::rotate(bare_tran, glm::radians(float(90.0)), glm::vec3(0.0, 1.0, 0.0));
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 0);
	shader.setFloat("material.shiness", 32.0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_shelf);
	for (int i = 0; i < length; i++) {
		glBindVertexArray(VAO[0]);
		model = glm::translate(bare_tran, glm::vec3(0.0, 0.95, 0.0));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(bare_tran, glm::vec3(0.0, -0.95, 0.0));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO[1]);
		model = glm::translate(bare_tran, glm::vec3(0.45, 0.0, 0.0));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		model = glm::translate(bare_tran, glm::vec3(-0.45, 0.0, 0.0));
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(VAO[2]);
		shader.setMat4("model", bare_tran);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		bare_tran = glm::translate(bare_tran, glm::vec3(1.0, 0.0, 0.0));
	}

	glBindVertexArray(0);
}

int Shelf::get_length() {
	return length;
}

bool Shelf::loadbox(int row, int column) {
	if (is_loaded[row][column]) return false;
	else {
		is_loaded[row][column] = true;
		return true;
	}
}

void Shelf::reset(int row, int column) {
	is_loaded[row][column] = false;
}

void Shelf::rotate() {
	is_x_axis = !is_x_axis;
	float* f = territory[index];
	if (is_x_axis) {
		f[0] = Position.x - 0.5;
		f[1] = Position.x + 0.5;
		f[2] = Position.z - length * 1.0 + 0.5;
		f[3] = Position.z + 0.5;
	}
	else {
		f[0] = Position.x - 0.5;
		f[1] = Position.x + length * 1.0 - 0.5;
		f[2] = Position.z - 0.5;
		f[3] = Position.z + 0.5;
	}
}