#ifndef UNLIT_MATERIAL_H_DEFINED
#define UNLIT_MATERIAL_H_DEFINED

#include "Material.h"

struct UnlitMaterial: public virtual Material {
  glm::vec4 m_color;
  GLint m_texture;

  UnlitMaterial(glm::vec4 in_color={1.0, 1.0, 1.0, 1.0}, GLint in_texture = -1): Material(),
  m_color(in_color), m_texture(in_texture) {

  }

  virtual ~UnlitMaterial();

  virtual void clear() override;

  virtual void init() override;

  virtual void internalBind() override;
};


#endif
