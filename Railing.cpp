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
#include "Railing.h"

std::vector<float> cub1;
std::vector<float> cub2;
unsigned int Railing::texture_railing = 0;
unsigned int Railing::VAO[2] = { 0,0 }; 
unsigned int Railing::VBO[2] = { 0,0 };

Railing::Railing(float x, float y, float z, bool x_axis, int Length) {
	type = RAILING;
	Position = glm::vec3(x, y + GROUND + 0.5, z);
	is_x_axis = x_axis;
	length = Length;
	index = current_index;
	current_index++;
	objects[index] = this;
	territory[index] = NULL;
}

void Railing::initial() {
	texture_railing = loadTexture("pic/railing.jpg");

	create_vertex(cub1, 0.05, 0.5, 0.05);
	create_vertex(cub2, 0.1, 0.05, 0.05);

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cub1.size(), &cub1[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cub2.size(), &cub2[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Railing::draw(Shader& shader) {
	glm::mat4 model(1.0f);
	glm::mat4 bare_tran(1.0f);
	bare_tran = glm::translate(bare_tran, Position);
	if(!is_x_axis) bare_tran = glm::rotate<float>(bare_tran, glm::radians(90.0), glm::vec3(0.0, 1.0, 0.0));
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 0);
	shader.setFloat("material.shiness", 32.0);
	for (int i = 0; i < 2 * length; i++) {
		shader.setMat4("model", bare_tran);
		glBindTexture(GL_TEXTURE_2D, texture_railing);
		glBindVertexArray(VAO[0]);
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(bare_tran, glm::vec3(0.15, 0.0, 0.0));
		shader.setMat4("model", model);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(bare_tran, glm::vec3(-0.15, 0.0, 0.0));
		shader.setMat4("model", model);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(bare_tran, glm::vec3(0.15, 0.45, 0.0));
		shader.setMat4("model", model);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::translate(bare_tran, glm::vec3(-0.15, 0.45, 0.0));
		shader.setMat4("model", model);
		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		bare_tran = glm::translate(bare_tran, glm::vec3(0.5, 0.0, 0.0));
	}
	
	glBindVertexArray(0);
}