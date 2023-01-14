#pragma once

const int T_STRIP = 30;
const float RADIUS = 0.1;

class Transporter : public Object {
public:
	Transporter(float x, float z, bool x_axis, int i_length);
	int GetLen();
	void draw(Shader& shader);
	void rotate(float deltaTime);
	void rotate();
	bool get_front();
	bool getbox(Object* Container);
	static void initial();
private:
	int length;
	bool is_x_axis;
	float tran_angle;
	std::vector<Object*> boxes;
	static unsigned int VAO[2], VBO[2];
	static unsigned int texture_tran1, texture_tran2;
};

