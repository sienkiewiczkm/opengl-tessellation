#include "bezierPatchEffect.hpp"
#include "config.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>

using namespace std;

BezierPatchEffect::BezierPatchEffect() {
}

void BezierPatchEffect::initialize(string shaderName) {
  string vertName = SHADER_PATH_PREFIX + shaderName + ".vert";
  string tescName = SHADER_PATH_PREFIX + shaderName + ".tesc";
  string teseName = SHADER_PATH_PREFIX + shaderName + ".tese";
  string fragName = SHADER_PATH_PREFIX + shaderName + ".frag";

  _vertexShader = 
    make_shared<VertexShader>(vertName);
  _tessalationControlShader = 
    make_shared<TessalationControlShader>(tescName);
  _tessalationEvaluationShader = 
    make_shared<TessalationEvaluationShader>(teseName);
  _fragmentShader = 
    make_shared<FragmentShader>(fragName);

  _shaderProgram = make_shared<ShaderProgram>();
  _shaderProgram->attach(_vertexShader.get());
  _shaderProgram->attach(_tessalationControlShader.get());
  _shaderProgram->attach(_tessalationEvaluationShader.get());
  _shaderProgram->attach(_fragmentShader.get());
  _shaderProgram->link();

  getUniformLocations();
}

void BezierPatchEffect::setProjectionMatrix(const glm::mat4 &projection) {
  _shaderProgram->setUniform(_uniforms.projectionMatrix, projection);
}

void BezierPatchEffect::setViewMatrix(const glm::mat4 &view) {
  _shaderProgram->setUniform(_uniforms.viewMatrix, view);
}

void BezierPatchEffect::setModelMatrix(const glm::mat4 &model) {
  _shaderProgram->setUniform(_uniforms.modelMatrix, model);
}

void BezierPatchEffect::setLightPosition(const glm::vec3 &position) {
  _shaderProgram->setUniform(_uniforms.lightPosition, position);
}

void BezierPatchEffect::setTessellationLevelBump(int levelBump) {
  _shaderProgram->setUniform(_uniforms.tessellationLevelBump, levelBump);
}

void BezierPatchEffect::begin() {
  glUseProgram(_shaderProgram->getId());
}

void BezierPatchEffect::end() {
}

void BezierPatchEffect::getUniformLocations() {
  memset(&_uniforms, 0, sizeof(BezierPatchEffectUniformLocations));
  _uniforms.projectionMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "projectionMatrix");
  _uniforms.viewMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "viewMatrix");
  _uniforms.modelMatrix =
    glGetUniformLocation(_shaderProgram->getId(), "modelMatrix");
  _uniforms.lightPosition =
    glGetUniformLocation(_shaderProgram->getId(), "lightPosition");
  _uniforms.tessellationLevelBump =
    glGetUniformLocation(_shaderProgram->getId(), "tessellationLevelBump");
}

