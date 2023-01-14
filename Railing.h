#pragma once
class Railing : public Object {
public:
	Railing(float x, float y, float z, bool x_axis, int Length);
	void draw(Shader& shader);
	static void initial();
private:
	bool is_x_axis;
	int length;
	static unsigned int texture_railing;
	static unsigned int VAO[2], VBO[2];
};