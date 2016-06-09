#ifndef __BEZIER_PATCH_EFFECT_HPP__
#define __BEZIER_PATCH_EFFECT_HPP__

#include <string>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "shaders.hpp"

struct BezierPatchEffectUniformLocations {
  GLuint projectionMatrix;
  GLuint viewMatrix;
  GLuint modelMatrix;
  GLuint tessLevelInner;
  GLuint tessLevelOuter;
};

class BezierPatchEffect {
public:
  BezierPatchEffect();
  void initialize(std::string shaderName);

  void setProjectionMatrix(const glm::mat4 &projection);
  void setViewMatrix(const glm::mat4 &view);
  void setModelMatrix(const glm::mat4 &model);

  void begin();
  void end();

protected:
  void getUniformLocations();

private:
  std::shared_ptr<VertexShader> _vertexShader;
  std::shared_ptr<TessalationControlShader> _tessalationControlShader;
  std::shared_ptr<TessalationEvaluationShader> _tessalationEvaluationShader;
  std::shared_ptr<FragmentShader> _fragmentShader;
  std::shared_ptr<ShaderProgram> _shaderProgram;

  BezierPatchEffectUniformLocations _uniforms;
};

#endif
