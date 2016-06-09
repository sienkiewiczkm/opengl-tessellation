#include "shaders.hpp"
#include "config.hpp"
#include <cstdio>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

Shader::Shader() : _shaderType(0), _shaderId(0) {
}

Shader::~Shader() {
  if (!_shaderId) {
    glDeleteShader(_shaderId);
    _shaderId = 0;
  }
}

void Shader::loadShaderFromFile(GLenum shaderType, string filename) {
  FILE *f = fopen(filename.c_str(), "rb");
  if (!f) {
    cerr << "Error: Cannot load shader: \"" << filename << "\"." << endl;
    return;
  }

  fseek(f, 0, SEEK_END);
  auto size = ftell(f);
  fseek(f, 0, SEEK_SET);
  char *shaderCode = new char[size+1];
  fread(shaderCode, size, 1, f);
  shaderCode[size] = 0;
  fclose(f);

  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderCode, nullptr); 
  glCompileShader(shader);
  delete[] shaderCode;

  GLint success;
  GLchar infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    cout << "Error: Shader compilation failed" << endl 
      << infoLog << endl;
    return; // todo: throw exception
  }

  _shaderType = shaderType;
  _shaderId = shader;
}

VertexShader::VertexShader(const string filename) {
  loadShaderFromFile(GL_VERTEX_SHADER, filename.c_str());
}

VertexShader::~VertexShader() {
}

FragmentShader::FragmentShader(const string filename) {
  loadShaderFromFile(GL_FRAGMENT_SHADER, filename.c_str());
}

FragmentShader::~FragmentShader() {
}

TessalationControlShader::TessalationControlShader(const string filename) {
  loadShaderFromFile(GL_TESS_CONTROL_SHADER, filename.c_str());
}

TessalationControlShader::~TessalationControlShader() {
}

TessalationEvaluationShader::TessalationEvaluationShader(
    const string filename
  ) {
  loadShaderFromFile(GL_TESS_EVALUATION_SHADER, filename.c_str());
}

TessalationEvaluationShader::~TessalationEvaluationShader() {
}

ShaderProgram::ShaderProgram() {
  _program = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
  if (_program) {
    glDeleteProgram(_program);
    _program = 0;
  }
}

void ShaderProgram::attach(Shader *shader) {
  glAttachShader(_program, shader->getId());
}

void ShaderProgram::link() {
  glLinkProgram(_program);

  GLint success;
  GLchar infoLog[512];
  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if (!success) {
      glGetProgramInfoLog(_program, 512, NULL, infoLog);
      std::cout << "Error: Shader link" << std::endl << infoLog << std::endl;
  }
}

void ShaderProgram::setUniform(GLuint location, const glm::mat4 &matrix) {
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::setUniform(GLuint location, const glm::vec3 &vec) {
  glUniform3fv(location, 1, glm::value_ptr(vec));
}

