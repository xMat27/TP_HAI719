#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
protected:
  // Shader program
  GLuint m_program;

  inline void check() {
    if (m_program == 0) {
      throw std::runtime_error("Shader program not initialized");
    }
  }

public:
  Material(): m_program(0) {

  }

  virtual ~Material() {
    if (m_program != 0) {
      glDeleteProgram(m_program);
    }
  }



  virtual void init() = 0;
  virtual void clear() = 0;


  void bind() {
    check();
    glUseProgram(m_program);
    internalBind();
  }
  virtual void internalBind() = 0;

  void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix) {
    check();
    glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
  }


  GLint getAttribute(const std::string& in_attributeName) {
    check();
    return glGetAttribLocation(m_program, in_attributeName.c_str());
  }

  GLint getUniform(const std::string& in_uniformName) {
    check();
    return glGetUniformLocation(m_program, in_uniformName.c_str());
  }
};

#endif
