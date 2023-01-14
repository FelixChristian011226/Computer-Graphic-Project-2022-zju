#pragma once
class Shelf: public Object {
public:
	Shelf(int x, int z, bool x_axis, int Length);
	bool get_front();
	int get_length();
	void rotate();
	void draw(Shader& shader);
	bool loadbox(int row, int column);
	void reset(int row, int column);
	static void initial();
private:
	int length;
	bool is_x_axis;
	bool* is_loaded[2];
	static unsigned int VAO[3], VBO[3];
	static unsigned int texture_shelf;
};