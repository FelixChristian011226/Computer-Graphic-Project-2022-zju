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
#include "Console.h"

unsigned int Console::texture_console = 0;
unsigned int Console::texture_display = 0;
unsigned int Console::VAO[2] = { 0,0 };
unsigned int Console::VBO[2] = { 0,0 };

float cub[] = {
	-0.5,  0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 1.0,
	-0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0,
	 0.0,  0.5, -0.5, 0.0, 0.0, -1.0, 0.5, 1.0,
	-0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0,
	 0.0,  0.5, -0.5, 0.0, 0.0, -1.0, 0.5, 1.0,
	 0.5,  0.0, -0.5, 0.0, 0.0, -1.0, 1.0, 0.5,
	-0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 0.0, 0.0,
	 0.5,  0.0, -0.5, 0.0, 0.0, -1.0, 1.0, 0.5,
	 0.5, -0.5, -0.5, 0.0, 0.0, -1.0, 1.0, 0.0,

	-0.5,  0.5,  0.5, 0.0, 0.0,  1.0, 0.0, 1.0,
	-0.5, -0.5,  0.5, 0.0, 0.0,  1.0, 0.0, 0.0,
	 0.0,  0.5,  0.5, 0.0, 0.0,  1.0, 0.5, 1.0,
	-0.5, -0.5,  0.5, 0.0, 0.0,  1.0, 0.0, 0.0,
	 0.0,  0.5,  0.5, 0.0, 0.0,  1.0, 0.5, 1.0,
	 0.5,  0.0,  0.5, 0.0, 0.0,  1.0, 1.0, 0.5,
	-0.5, -0.5,  0.5, 0.0, 0.0,  1.0, 0.0, 0.0,
	 0.5,  0.0,  0.5, 0.0, 0.0,  1.0, 1.0, 0.5,
	 0.5, -0.5,  0.5, 0.0, 0.0,  1.0, 1.0, 0.0,

	-0.5,  0.5, -0.5, -1.0, 0.0, 0.0, 1.0, 1.0,
	-0.5, -0.5,  0.5, -1.0, 0.0, 0.0, 0.0, 0.0,
	-0.5,  0.5,  0.5, -1.0, 0.0, 0.0, 0.0, 1.0,
	-0.5,  0.5, -0.5, -1.0, 0.0, 0.0, 1.0, 1.0,
	-0.5, -0.5,  0.5, -1.0, 0.0, 0.0, 0.0, 0.0,
	-0.5, -0.5, -0.5, -1.0, 0.0, 0.0, 1.0, 0.0,

	 0.5, -0.5, -0.5,  1.0, 0.0, 0.0, 0.0, 0.0,
	 0.5,  0.0,  0.5,  1.0, 0.0, 0.0, 1.0, 1.0,
	 0.5,  0.0, -0.5,  1.0, 0.0, 0.0, 0.0, 1.0,
	 0.5, -0.5, -0.5,  1.0, 0.0, 0.0, 0.0, 0.0,
	 0.5,  0.0,  0.5,  1.0, 0.0, 0.0, 1.0, 1.0,
	 0.5, -0.5,  0.5,  1.0, 0.0, 0.0, 1.0, 0.0,

	 0.0,  0.5,  0.5, 0.0,  1.0, 0.0, 1.0, 1.0,
	-0.5,  0.5, -0.5, 0.0,  1.0, 0.0, 0.0, 0.0,
	-0.5,  0.5,  0.5, 0.0,  1.0, 0.0, 0.0, 1.0,
	 0.0,  0.5,  0.5, 0.0,  1.0, 0.0, 1.0, 1.0,
	-0.5,  0.5, -0.5, 0.0,  1.0, 0.0, 0.0, 0.0,
	 0.0,  0.5, -0.5, 0.0,  1.0, 0.0, 1.0, 0.0,

	 0.5, -0.5,  0.5, 0.0, -1.0, 0.0, 1.0, 1.0,
	-0.5, -0.5, -0.5, 0.0, -1.0, 0.0, 0.0, 0.0,
	-0.5, -0.5,  0.5, 0.0, -1.0, 0.0, 0.0, 1.0,
	 0.5, -0.5,  0.5, 0.0, -1.0, 0.0, 1.0, 1.0,
	-0.5, -0.5, -0.5, 0.0, -1.0, 0.0, 0.0, 0.0,
	 0.5, -0.5, -0.5, 0.0, -1.0, 0.0, 1.0, 0.0,
};

float display[] = {
	0.5, 0.0, -0.5, 1.0, 1.0, 0.0, 0.0, 0.0,
	0.0, 0.5,  0.5, 1.0, 1.0, 0.0, 1.0, 1.0,
	0.0, 0.5, -0.5, 1.0, 1.0, 0.0, 0.0, 1.0,
	0.5, 0.0, -0.5, 1.0, 1.0, 0.0, 0.0, 0.0,
	0.0, 0.5,  0.5, 1.0, 1.0, 0.0, 1.0, 1.0,
	0.5, 0.0,  0.5, 1.0, 1.0, 0.0, 1.0, 0.0
};

void Console::initial() {
	texture_console = loadTexture("pic/console.jpg");
	texture_display = loadTexture("pic/display.jpg");

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cub), cub, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(display), display, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Console::Console(float x, float z, int front) {
	type = CONSOLE;
	Position = glm::vec3(x, 4.01+GROUND + 0.5, z);
	Front = front;
	index = current_index;
	current_index++;
	objects[index] = this;
	float* f = new float[4];
	f[0] = x - 0.5;
	f[1] = x + 0.5;
	f[2] = z - 0.5;
	f[3] = z + 0.5;
	territory[index] = f;
}

int Console::GetFront() {
	return Front;
}

bool Console::is_nearby(glm::vec3 Pos) {
	float x = Pos.x - Position.x;
	float z = Pos.z - Position.z;
	if (x * x + z * z > 9) {
		return false;
	}
	else {
		return true;
	}
}

bool Console::SetFront(int front) {
	if (front == 0 || front == 90 || front == 180 || front == 270) {
		Front = front;
		return true;
	}
	else {
		std::cout << ">illegal angle in Console::SetFront<\n";
		return false;
	}
}

void Console::draw(Shader& shader) {
	glm::mat4 model(1.0f);
	model = glm::translate(model, Position);
	model = glm::rotate<float>(model, glm::radians(float(Front)), glm::vec3(0.0, 1.0, 0.0));
	shader.use();
	shader.setMat4("model", model);
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 0);
	shader.setFloat("material.shiness", 32.0);
	glBindVertexArray(VAO[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_console);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(VAO[1]);
	glBindTexture(GL_TEXTURE_2D, texture_display);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	territory[index][0] = Position.x - 0.5;
	territory[index][1] = Position.x + 0.5;
	territory[index][2] = Position.z - 0.5;
	territory[index][3] = Position.z + 0.5;
}