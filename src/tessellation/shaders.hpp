#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <GL/glew.h>
#include <string>
#include <glm/mat4x4.hpp>

class Shader {
public:
  Shader();
  Shader(const Shader &shader) = default;
  virtual ~Shader();

  GLenum getType() { return _shaderType; }
  GLuint getId() { return _shaderId; }

protected:
  void loadShaderFromFile(GLenum shaderType, std::string filename);

private:
  GLenum _shaderType;
  GLuint _shaderId;
};

class VertexShader : public Shader {
public:
  VertexShader(const std::string filename);
  virtual ~VertexShader();
};

class FragmentShader : public Shader {
public:
  FragmentShader(const std::string filename);
  virtual ~FragmentShader();
};

class TessalationControlShader : public Shader {
public:
  TessalationControlShader(const std::string filename);
  virtual ~TessalationControlShader();
};

class TessalationEvaluationShader : public Shader {
public:
  TessalationEvaluationShader(const std::string filename);
  virtual ~TessalationEvaluationShader();
};

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();

  void attach(Shader *shader);
  void link();
  GLuint getId() { return _program; }

  void setUniform(GLuint location, const glm::mat4 &matrix);
  void setUniform(GLuint location, const glm::vec3 &vec);
  void setUniform(GLuint location, GLint value);

private:
  GLuint _program;
};

#endif
