#pragma once

const float GROUND = -0.4;

enum object_type {
	FORKLIFT = 0,
	CONTAINER,
	SHELF,
	TRANSPORTER,
	CONSOLE,
	RAILING
};

class Object {
public:
	glm::vec3 getPos();
	void SetPos(glm::vec3 Pos);
	void SetPos(float x, float y, float z);
	void SetType(object_type i_type);
	int GetIndex();
	object_type GetType();
	virtual void draw(Shader& shader) = 0;
	static void select(int index);
	static void DrawFrame(Shader& shader);
	static void init_line();
	static std::map<int, Object*> objects;
	static std::map<int, float*> territory;
	
protected:
	glm::vec3 Position;
	int index;
	object_type type;
	static int current_index;
	static int selected;

private:
	static unsigned int VAO, VBO, EBO;
	static unsigned int indices[24];
};