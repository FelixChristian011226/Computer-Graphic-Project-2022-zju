#pragma once
class Container: public Object{
public:
	Container(int x, int z, int des);
	void SetAng(float Angle);
	void draw(Shader& shader);
	void resetShelf();
	void setShelf(Object* i_shelf, int i_row, int i_column);
	static void initial();
private:
	Object* depend;
	int row, column;
	float angle;
	static int texture_box, texture_box_specular;
	static unsigned int VAO, VBO;
};