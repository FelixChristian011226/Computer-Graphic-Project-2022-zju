#pragma once
#define FLOORVSIZE 32
#define FLOORISIZE 6
class floors {
public:
	floors(const std::string inputpic, const float vertices[], const int indices[]);
	void draw(Shader& area);
	void initial();
private:
	std::string face;
	float floorVertices[FLOORVSIZE];
	int floorIndices[FLOORVSIZE];
	unsigned int fVAO, fVBO, fEB0;
	unsigned int texture_floor;
};