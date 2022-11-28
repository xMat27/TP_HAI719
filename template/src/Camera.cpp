// **************************************************
// GLRK : the OpenGL Refinement Kernel.
// Camera.
// This file is a part of the GLRK library.
// Author : Tamy Boubekeur (Tamy.Boubekeur@labri.fr).
// Copyright (C) 2006 Tamy Boubekeur.
// All rights reserved.
// **************************************************

#include "Camera.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

#include <glm/gtc/quaternion.hpp>
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective

using namespace std;

static int _spinning, _moving;
static int _beginu, _beginv;
static float _curquat[4];
static float _x, _y, _z;
static float __zoom;
static bool ini = false;

Camera::Camera () {
  fovAngle = 65.0;
  aspectRatio = 1.0;
  nearPlane = 0.001;
  farPlane = 10000.0;

  spinning = 0;
  moving = 0;
  beginu = 0;
  beginv = 0;

  trackball (current, 0.0, 0.0, 0.0, 0.0);
  x = y = z = 10.0;
  _zoom = 3.0;
}


void Camera::resize (int _W, int _H) {
  H = _H;
  W = _W;
  aspectRatio = (float)W /(float)H;
  glViewport (0, 0, (GLint)W, (GLint)H);
}


void Camera::initPos () {
  if (!ini) {
  _spinning = spinning;
  _moving = moving;
  _beginu = beginu;
  _beginv = beginv;
  _curquat[0] = curquat[0];
  _curquat[1] = curquat[1];
  _curquat[2] = curquat[2];
  _curquat[3] = curquat[3];
  _x = x;
  _y = y;
  _z = z;;
  __zoom = _zoom;
  ini = true;
  } else {
    spinning = _spinning;
    moving = _moving;;
    beginu = _beginu;
    beginv = _beginv;
    curquat[0] = _curquat[0];
    curquat[1] = _curquat[1];
    curquat[2] = _curquat[2];
    curquat[3] = _curquat[3];
    x = _x;
    y = _y;
    z = _z;;
    _zoom = __zoom;
  }
}


void Camera::move (float dx, float dy, float dz) {
  x += dx;
  y += dy;
  z += dz;
}


void Camera::beginRotate (int u, int v) {
  beginu = u;
  beginv = v;
  moving = 1;
  spinning = 0;
}


void Camera::rotate (int u, int v) {
  if (moving) {
    trackball(lastquat,
	      (2.0 * beginu - W) / W,
	      (H - 2.0 * beginv) / H,
	      (2.0 * u - W) / W,
	      (H - 2.0 * v) / H);
    beginu = u;
    beginv = v;
    spinning = 1;
    add_quats (lastquat, curquat, curquat);
  }
}


void Camera::endRotate () {
  moving = false;
}

void Camera::lookAt(glm::vec3 target) {
  glm::mat4 lookMat = glm::lookAt(position, target, glm::vec3(0, 1, 0));
  current = glm::conjugate(glm::quat_cast(lookMat));
}

glm::mat4 Camera::getViewMatrix() {
  glm::mat4 view = glm::mat4_cast(current) * glm::translate(glm::mat4(1), position);
  return view;
}

glm::mat4 Camera::getProjectionMatrix() {
  glm::mat4 projection = glm::perspective(
    glm::radians(fovAngle),
    static_cast<float>(W)/static_cast<float>(H),
    nearPlane,
    farPlane
  );
  return projection;
}
