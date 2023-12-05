#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>

struct Material {
	// Shader program
	GLuint m_program;
	GLuint m_program_sky;
	GLuint m_program_mesh;

	// Material parameters
	glm::vec4 m_color;
	GLint m_texture;
	GLint m_normal;
	glm::vec3 m_lightColor;
	glm::vec3 m_lightPos;

	unsigned int cubemapTexture;
	unsigned int skyboxVAO, skyboxVBO;

	inline void check() {
		if (m_program_sky == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
		if (m_program_mesh == 0) {
			throw std::runtime_error("Shader program not initialized");
		}
	}

	Material(): m_program(0) {

	}

	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind(int idx);

	virtual void internalBind(int idx);

	void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

	GLint getAttribute(const std::string& in_attributeName);

	GLint getUniform(const std::string& in_uniformName);
};

#endif
