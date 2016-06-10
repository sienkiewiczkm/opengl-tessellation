#ifndef __BEZIER_CONTROL_NET_EFFECT_HPP__
#define __BEZIER_CONTROL_NET_EFFECT_HPP__

#include "effectBase.hpp"
#include "shaders.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <string>

class BezierControlNetEffect : public EffectBase {
public:
  BezierControlNetEffect();
  void initialize(std::string shaderName);

  void setProjectionMatrix(const glm::mat4 &projection);
  void setViewMatrix(const glm::mat4 &view);
  virtual void setModelMatrix(const glm::mat4 &model);

  void begin();
  void end();

private:
  void getUniformLocations();

  std::shared_ptr<VertexShader> _vertexShader;
  std::shared_ptr<FragmentShader> _fragmentShader;
  std::shared_ptr<ShaderProgram> _shaderProgram;

  struct BezierControlNetEffectUniforms {
    GLuint projectionMatrix;
    GLuint viewMatrix;
    GLuint modelMatrix;
  };

  BezierControlNetEffectUniforms _uniforms;
};

#endif
