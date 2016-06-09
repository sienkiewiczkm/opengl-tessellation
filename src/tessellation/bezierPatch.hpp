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
  void createFromHeightmap(float width, float length, 
    std::vector<float> heightmap);
  void setControlPoints(const std::vector<glm::vec3> &controlPoints);
  void drawPatch() const;
  void drawControlNet() const;

private:
  GLuint _vao, _vbo;
  GLuint _vaoControl, _eboControl;
  GLuint _controlNumElements;
};

#endif
