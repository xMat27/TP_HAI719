#ifndef CAMERA_H_DEFINED
#define CAMERA_H_DEFINED

#include "Trackball.h"

#include <glm/glm.hpp>

class Camera {
public:
  Camera ();
  virtual ~Camera () {}

  inline float getFovAngle () const { return fovAngle; }
  inline void setFovAngle (float newFovAngle) { fovAngle = newFovAngle; }
  inline float getAspectRatio () const { return aspectRatio; }
  inline float getNearPlane () const { return nearPlane; }
  inline void setNearPlane (float newNearPlane) { nearPlane = newNearPlane; }
  inline float getFarPlane () const { return farPlane; }
  inline void setFarPlane (float newFarPlane) { farPlane = newFarPlane; }
  inline unsigned int getScreenWidth () const { return W; }
  inline unsigned int getScreenHeight () const { return H; }

  void resize (int W, int H);
  void move (float dx, float dy, float dz);
  void beginRotate (int u, int v);
  void rotate (int u, int v);
  void endRotate ();
  void zoom (float z);

  glm::mat4 getViewMatrix();
  glm::mat4 getProjectionMatrix();

  // void lookAt (glm::vec3, eye, glm::vec3 target, glm::vec3 up);
  // void lookAt (float x, float y, float z);
  // void setPos (float x, float y, float z);
  // void getPos (float & x, float & y, float & z);
  // inline void getPos (glm::vec3 & p) { getPos (p[0], p[1], p[2]); }

private:
  float fovAngle;
  float aspectRatio;
  float nearPlane;
  float farPlane;

  int spinning, moving;
  int beginu, beginv;
  int H, W;
  glm::mat4 projection;
  glm::mat4 view;
  glm::quat current;
  glm::quat last;
  glm::vec3 position;
  float _zoom;
};

#endif // CAMERA_H
// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
