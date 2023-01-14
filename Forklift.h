#pragma once

const float CAR_SPEED = 2.0;
const float ANGULAR_SPEED = 180.0;
const int C_STRIP = 30;
const float TYRE_SIZE = 0.4;

class Forklift: public Object {
public:
	Forklift(float x, float z, int front = 90);
	bool forward(float x, float deltaTime);
	bool rotate(bool left);
	bool backward(float x, float deltaTime);
	bool rise(int x, float deltaTime);
	bool decline(float deltaTime);
	bool getbox(Object* container);
	bool dropbox();
	bool storebox(Object* depend);
	void draw(Shader& shader);
    static void initial();
	Object* box;
private:
	int Front;
	float fork_y;
	float tyre_angle;
	

	void forward(float v);

	static unsigned int VAO[6], VBO[6];
	static unsigned int texture_fork, texture_cab, texture_body, texture_tyre, texture_tyre2, texture_frame;
};