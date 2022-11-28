// Local includes
#include "UnlitMaterial.h"
#include "Shader.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

UnlitMaterial::~UnlitMaterial() {

}

void UnlitMaterial::init() {
  m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
  check();
}

void UnlitMaterial::clear() {
  // nothing to clear
}

void UnlitMaterial::internalBind() {
  GLint color = getUniform("color");
  glUniform4fv(color, 1, glm::value_ptr(m_color));
  if (m_texture != -1) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(getUniform("colorTexture"), GL_TEXTURE0);
  }
}
