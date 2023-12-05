// Local includes
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Context.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>

Material::~Material() {
	if (m_program != 0) {
		glDeleteProgram(m_program);
	}
}

void Material::init() {
	// TODO : Change shader by your
	m_program_mesh = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	m_program_sky = load_shaders("shaders/unlit/skyvertex.glsl", "shaders/unlit/skyfragment.glsl");
	check();
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};
	m_lightPos = {0.5, 1, 0.5};
	m_lightColor = {1.0, 1.0, 1.0};
	m_texture = loadTexture2DFromFilePath("data/WaterBottle_baseColor.png");
	m_normal = loadTexture2DFromFilePath("data/WaterBottle_normal.png");

    unsigned int albedo    = loadTexture2DFromFilePath("resources/textures/pbr/rusted_iron/albedo.png");
    unsigned int normal    = loadTexture2DFromFilePath("resources/textures/pbr/rusted_iron/normal.png");
    unsigned int metallic  = loadTexture2DFromFilePath("resources/textures/pbr/rusted_iron/metallic.png");
    unsigned int roughness = loadTexture2DFromFilePath("resources/textures/pbr/rusted_iron/roughness.png");
    unsigned int ao        = loadTexture2DFromFilePath("resources/textures/pbr/rusted_iron/ao.png");

	float skyboxVertices[] = {
        // positions          
        -20.0f,  20.0f, -20.0f,
        -20.0f, -20.0f, -20.0f,
         20.0f, -20.0f, -20.0f,
         20.0f, -20.0f, -20.0f,
         20.0f,  20.0f, -20.0f,
        -20.0f,  20.0f, -20.0f,

        -20.0f, -20.0f,  20.0f,
        -20.0f, -20.0f, -20.0f,
        -20.0f,  20.0f, -20.0f,
        -20.0f,  20.0f, -20.0f,
        -20.0f,  20.0f,  20.0f,
        -20.0f, -20.0f,  20.0f,

         20.0f, -20.0f, -20.0f,
         20.0f, -20.0f,  20.0f,
         20.0f,  20.0f,  20.0f,
         20.0f,  20.0f,  20.0f,
         20.0f,  20.0f, -20.0f,
         20.0f, -20.0f, -20.0f,

        -20.0f, -20.0f,  20.0f,
        -20.0f,  20.0f,  20.0f,
         20.0f,  20.0f,  20.0f,
         20.0f,  20.0f,  20.0f,
         20.0f, -20.0f,  20.0f,
        -20.0f, -20.0f,  20.0f,

        -20.0f,  20.0f, -20.0f,
         20.0f,  20.0f, -20.0f,
         20.0f,  20.0f,  20.0f,
         20.0f,  20.0f,  20.0f,
        -20.0f,  20.0f,  20.0f,
        -20.0f,  20.0f, -20.0f,

        -20.0f, -20.0f, -20.0f,
        -20.0f, -20.0f,  20.0f,
         20.0f, -20.0f, -20.0f,
         20.0f, -20.0f, -20.0f,
        -20.0f, -20.0f,  20.0f,
         20.0f, -20.0f,  20.0f
    };


    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces
	{
    "data/Skybox/right.jpg",
    "data/Skybox/left.jpg",
    "data/Skybox/top.jpg",
    "data/Skybox/bottom.jpg",
    "data/Skybox/front.jpg",
    "data/Skybox/back.jpg",
	};
	cubemapTexture = loadCubemap(faces);  
    std::cout <<"cubemap :"<<cubemapTexture << std::endl;

}

void Material::clear() {
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
}

void Material::bind(int idx) {
    check();
    if(idx == 0){
        m_program = m_program_sky;
    } else {
        m_program = m_program_mesh;
    }
    glUseProgram(m_program);
    internalBind(idx);
}


void Material::internalBind(int idx) {
	if(idx == 0){
        glDepthFunc(GL_LEQUAL);
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    } else {
	// bind parameters
	GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));
	if (m_texture != -1) {
		glUniform1i(getUniform("colorTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
	if (m_normal != -1) {
		glUniform1i(getUniform("normalMap"), 1);
		glActiveTexture(GL_TEXTURE0+ 1);
		glBindTexture(GL_TEXTURE_2D, m_normal);
	}
	}
	glUniform3fv(getUniform("viewPos"), 1, glm::value_ptr(Context::camera.position));
	glUniform3fv(getUniform("lightPos"), 1, glm::value_ptr(m_lightPos));
	GLint light = getUniform("lightColor");
	glUniform3fv(light, 1, glm::value_ptr(m_lightColor));


	// TODO : Add your custom parameters here
}

void Material::setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}

GLint Material::getAttribute(const std::string& in_attributeName) {
	check();
	return glGetAttribLocation(m_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string& in_uniformName) {
	check();
	return glGetUniformLocation(m_program, in_uniformName.c_str());
}
