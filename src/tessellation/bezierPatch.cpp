#include "bezierPatch.hpp"

using namespace std;

BezierPatch::BezierPatch() {
}

BezierPatch::BezierPatch(const vector<glm::vec3> &controlPoints) {
  setControlPoints(controlPoints);
}

void BezierPatch::createFlatGrid(float width, float length) {
  vector<glm::vec3> controlPoints;
  float stepWidth = width / 3.0f;
  float stepLength = length / 3.0f;
  float halfWidth = 0.5f * width;
  float halfLength = 0.5f * length;

  for (int z = 0; z < 4; ++z) {
    for (int x = 0; x < 4; ++x) {
      glm::vec3 point;
      point.x = x * stepWidth - halfWidth;
      point.y = 0.0f;
      point.z = z * stepLength - halfLength;
      controlPoints.push_back(point);
    }
  }

  assert(controlPoints.size() == 16);
  setControlPoints(controlPoints);
}

void BezierPatch::setControlPoints(const vector<glm::vec3> &controlPoints) {
  assert(controlPoints.size() == 16); 

  glGenVertexArrays(1, &_vao);
  glBindVertexArray(_vao);

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(
    GL_ARRAY_BUFFER, 
    sizeof(glm::vec3)*controlPoints.size(), 
    &controlPoints[0], 
    GL_STATIC_DRAW
  );

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(
      0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0
  );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


void BezierPatch::drawPatch() const {
  glBindVertexArray(_vao);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPatchParameteri(GL_PATCH_VERTICES, 16);
  glDrawArrays(GL_PATCHES, 0, 16);
}
