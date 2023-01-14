#pragma once
#pragma once
#define ROOFSIZE 150
class roof {
public:
	roof(const std::string inputpic, const float vertices[]);
	void draw(Shader& area);
	void initial();
private:
	std::string face;
	float roofVertices[ROOFSIZE];
	unsigned int rVAO, rVBO;
	unsigned int texture_roof;
};