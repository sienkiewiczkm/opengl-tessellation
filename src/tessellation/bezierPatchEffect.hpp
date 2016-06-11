#ifndef __BEZIER_PATCH_EFFECT_HPP__
#define __BEZIER_PATCH_EFFECT_HPP__

#include "effectBase.hpp"
#include "shaders.hpp"

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <string>

struct BezierPatchEffectUniformLocations {
  GLuint projectionMatrix;
  GLuint viewMatrix;
  GLuint modelMatrix;
  GLuint lightPosition;
  GLuint tessellationLevelBump;
  GLuint patchesNumU;
  GLuint patchesNumV;
  GLuint uPatch;
  GLuint vPatch;
  GLuint diffuseTexture;
  GLuint normalTexture;
  GLuint displacementTexture;
};

class BezierPatchEffect : public EffectBase {
public:
  BezierPatchEffect();
  void initialize(std::string shaderName);

  void setProjectionMatrix(const glm::mat4 &projection);
  void setViewMatrix(const glm::mat4 &view);
  virtual void setModelMatrix(const glm::mat4 &model);
  void setLightPosition(const glm::vec3 &position);
  void setTessellationLevelBump(int levelBump);
  void setPatchesNumU(int uPatches);
  void setPatchesNumV(int vPatches);
  void setPatchU(int patch);
  void setPatchV(int patch);

  void setDiffuseTexture(GLuint texture);
  void setNormalTexture(GLuint texture);
  void setDisplacementTexture(GLuint texture);

  void begin();
  void end();

private:
  void getUniformLocations();

  std::shared_ptr<VertexShader> _vertexShader;
  std::shared_ptr<TessalationControlShader> _tessalationControlShader;
  std::shared_ptr<TessalationEvaluationShader> _tessalationEvaluationShader;
  std::shared_ptr<FragmentShader> _fragmentShader;
  std::shared_ptr<ShaderProgram> _shaderProgram;

  BezierPatchEffectUniformLocations _uniforms;
};

#endif
