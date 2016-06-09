#include "orbitingCamera.hpp"

#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

OrbitingCamera::OrbitingCamera() :
  _xMin(-0.5f*M_PI), _xMax(0.5f*M_PI),
  _dist(1.0f),
  _rotationX(0.0f), _rotationY(0.0f) {
}

void OrbitingCamera::rotate(float dx, float dy) {
  _rotationX += dx;
  _rotationY += dy;

  if (_rotationX < _xMin) {
    _rotationX = _xMin;
  }

  if (_rotationX > _xMax) {
    _rotationX = _xMax;
  }

  while (_rotationY > 2.0f*M_PI)
    _rotationY -= 2.0f*M_PI;
  while (_rotationY < -2.0f*M_PI)
    _rotationY += 2.0f*M_PI;
 
}

glm::mat4 OrbitingCamera::getViewMatrix() {
  return glm::lookAt(
      glm::vec3(getPosition()),
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(0.0f, 1.0f, 0.0f)
    );
}

glm::vec3 OrbitingCamera::getPosition() {
  glm::vec4 cameraStartPosition(0.0f, 0.0f, -_dist, 1.0f);
  glm::mat4 cameraPositionTransform = glm::rotate(glm::mat4(1.0f),
    _rotationY, glm::vec3(0.0f, 1.0f, 0.0f));
  cameraPositionTransform = glm::rotate(cameraPositionTransform,
    _rotationX, glm::vec3(1.0f, 0.0f, 0.0f));
  return cameraPositionTransform * cameraStartPosition;
}
