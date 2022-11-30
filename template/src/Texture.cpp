#include "Texture.sh"

#include <GL/glut.h>

GLuint loadTexture2DFromFilePath(const std::string& path) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindBuffer(GL_TEXTURE_2D, texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 3);
	if (!data) {
		throw std::runtime_error("Failed to load texture: " + path);
	} else {
		glTexImage2D();
	}


	return texture;
}

void setDefaultTexture2DParameters(GLint in_texture);
