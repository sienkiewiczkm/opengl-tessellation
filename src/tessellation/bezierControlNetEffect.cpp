#include "bezierControlNetEffect.hpp"
#include "config.hpp"

using namespace std;

BezierControlNetEffect::BezierControlNetEffect() {
}

void BezierControlNetEffect::initialize(string shaderName) {
  string vertName = SHADER_PATH_PREFIX + shaderName + ".vert";
  string fragName = SHADER_PATH_PREFIX + shaderName + ".frag";

  _vertexShader = make_shared<VertexShader>(vertName);
  _fragmentShader = make_shared<FragmentShader>(fragName);
  _shaderProgram = make_shared<ShaderProgram>();
  _shaderProgram->attach(_vertexShader.get());
  _shaderProgram->attach(_fragmentShader.get());
  _shaderProgram->link();

  getUniformLocations();
}

void BezierControlNetEffect::setProjectionMatrix(const glm::mat4 &projection) {
  _shaderProgram->setUniform(_uniforms.projectionMatrix, projection);
}

void BezierControlNetEffect::setViewMatrix(const glm::mat4 &view) {
  _shaderProgram->setUniform(_uniforms.viewMatrix, view);
}

void BezierControlNetEffect::setModelMatrix(const glm::mat4 &model) {
  _shaderProgram->setUniform(_uniforms.modelMatrix, model);
}

void BezierControlNetEffect::begin() {
  glUseProgram(_shaderProgram->getId());
}

void BezierControlNetEffect::end() {
}

void BezierControlNetEffect::getUniformLocations() {
  memset(&_uniforms, 0, sizeof(BezierControlNetEffectUniforms));

  _uniforms.projectionMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "projectionMatrix");
  _uniforms.viewMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "viewMatrix");
  _uniforms.modelMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "modelMatrix");
}
