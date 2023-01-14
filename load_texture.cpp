#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <vector>
#include "stb_image.h"
#include "load_texture.h"

unsigned int loadTexture(char const* path){
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void create_vertex(std::vector<float>& array, float x, float y, float z) {
	array.push_back(float(x)); array.push_back(y); array.push_back(-z); array.push_back(0.0); array.push_back(0); array.push_back(-1); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(0); array.push_back(-1); array.push_back(1); array.push_back(0);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(0); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(1);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(0); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(0); array.push_back(-1); array.push_back(1); array.push_back(0);
	array.push_back(-x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(0);

	array.push_back(x); array.push_back(y); array.push_back(-z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(-z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(y); array.push_back(z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(y); array.push_back(z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(-z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(-y); array.push_back(z); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(0);

	array.push_back(x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(0);
	array.push_back(-x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1); array.push_back(1);
	array.push_back(-x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(0);
	array.push_back(-x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1); array.push_back(0);

	array.push_back(-x); array.push_back(y); array.push_back(z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(1);
	array.push_back(-x); array.push_back(-y); array.push_back(z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(-x); array.push_back(-y); array.push_back(z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(-x); array.push_back(-y); array.push_back(-z); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(1); array.push_back(0);

	array.push_back(-x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(1);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(y); array.push_back(z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(-x); array.push_back(y); array.push_back(-z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(y); array.push_back(-z); array.push_back(0); array.push_back(1); array.push_back(0); array.push_back(1); array.push_back(0);

	array.push_back(-x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(1);
	array.push_back(-x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(x); array.push_back(-y); array.push_back(z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(1); array.push_back(1);
	array.push_back(-x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(0); array.push_back(0);
	array.push_back(x); array.push_back(-y); array.push_back(-z); array.push_back(0); array.push_back(-1); array.push_back(0); array.push_back(1); array.push_back(0);
}