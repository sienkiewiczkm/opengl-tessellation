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

  glUseProgram(_shaderProgram->getId());
  _shaderProgram->setUniform(_uniforms.diffuseTexture, 0);
  _shaderProgram->setUniform(_uniforms.normalTexture, 1);
  _shaderProgram->setUniform(_uniforms.displacementTexture, 2);
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

void BezierPatchEffect::setPatchesNumU(int uPatches) {
  _shaderProgram->setUniform(_uniforms.patchesNumU, uPatches);
}

void BezierPatchEffect::setPatchesNumV(int vPatches) {
  _shaderProgram->setUniform(_uniforms.patchesNumV, vPatches);
}

void BezierPatchEffect::setPatchU(int patch) {
  _shaderProgram->setUniform(_uniforms.uPatch, patch);
}

void BezierPatchEffect::setPatchV(int patch) {
  _shaderProgram->setUniform(_uniforms.vPatch, patch);
}

void BezierPatchEffect::setDiffuseTexture(GLuint texture) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void BezierPatchEffect::setNormalTexture(GLuint texture) {
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture);
}

void BezierPatchEffect::setDisplacementTexture(GLuint texture) {
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, texture);
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
  _uniforms.patchesNumU =
    glGetUniformLocation(_shaderProgram->getId(), "patchesNumU");
  _uniforms.patchesNumV =
    glGetUniformLocation(_shaderProgram->getId(), "patchesNumV");
  _uniforms.uPatch =
    glGetUniformLocation(_shaderProgram->getId(), "uPatch");
  _uniforms.vPatch =
    glGetUniformLocation(_shaderProgram->getId(), "vPatch");
  _uniforms.diffuseTexture =
    glGetUniformLocation(_shaderProgram->getId(), "diffuseTexture");
  _uniforms.normalTexture =
    glGetUniformLocation(_shaderProgram->getId(), "normalTexture");
  _uniforms.displacementTexture =
    glGetUniformLocation(_shaderProgram->getId(), "displacementTexture");
}

