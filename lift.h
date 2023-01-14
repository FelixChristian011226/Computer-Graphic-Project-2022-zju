#pragma once
#define LIFTSIZE 150
class elift {
public:
	elift(const std::string inputpic, const float vertices[]);
	float draw(float x, float y, float z, Shader& lift, int& upflag, int& protect1,
		int& uprotect1, float& locy, int& protect3, int& floor1,
		int& openflag, int& protect2, int& uprotect, int& in_it,
		float& loc1, int& protect, float& loc, int& openflag1, glm::vec3 camera);
	void initial();
	int inlift(glm::vec3 camera);
private:
	std::string face;
	float liftVertices[LIFTSIZE];
	unsigned int lVAO, lVBO;
	unsigned int texture_lift;
};