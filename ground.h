#pragma once
#define GROUNDVSIZE 32
#define GROUNDISIZE 6
class ground {
public:
	ground(const std::string inputpic, const float vertices[], const int indices[]);
	void draw(Shader& area);
	void initial();
private:
	std::string face;
	float groundVertices[GROUNDVSIZE];
	int groundIndices[GROUNDVSIZE];
	unsigned int fVAO, fVBO, fEB0;
	unsigned int texture_ground;
};