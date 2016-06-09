#ifndef __BEZIER_PATCH_HPP__
#define __BEZIER_PATCH_HPP__

#include <vector>
#include <GL/glew.h>
#include <glm/vec3.hpp>

class BezierPatch {
public:
  BezierPatch();
  BezierPatch(const std::vector<glm::vec3> &controlPoints);

  void createFlatGrid(float width, float length);
  void setControlPoints(const std::vector<glm::vec3> &controlPoints);
  void drawPatch() const;

private:
  GLuint _vao, _vbo;
};

#endif
