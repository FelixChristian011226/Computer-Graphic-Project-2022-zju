#pragma once

class Console : public Object {
public:
	Console(float x, float z, int front = 90);
	bool is_nearby(glm::vec3 Pos);
	bool SetFront(int front);
	int GetFront();
	void draw(Shader& shader);
	static void initial();
private:
	int Front;
	static unsigned int VAO[2], VBO[2];
	static unsigned int texture_display, texture_console;
};