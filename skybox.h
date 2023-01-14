#pragma once
#define BOXSIZE 108
class skybox {
public:
	skybox(const std::string inputpic[], const float vertices[]);
	void draw();
	void initial();
	unsigned int loadCubemap(std::string faces[], int size);
private:
	std::string faces[6];
	float skyboxVertices[BOXSIZE];
	unsigned int sVAO, sVBO;
	unsigned int texture_skybox;
};