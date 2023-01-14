#pragma once
#define WALLSIZE 150
class wall {
public:
	wall(const std::string inputpic, const float vertices[]);
	void draw(Shader& area);
	void initial();
private:
	std::string face;
	float wallVertices[WALLSIZE];
	unsigned int wVAO, wVBO;
	unsigned int texture_wall;
};