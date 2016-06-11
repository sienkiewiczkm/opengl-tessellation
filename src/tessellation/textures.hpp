#ifndef __TEXTURES_HPP__
#define __TEXTURES_HPP__

#include <GL/glew.h>
#include <string>
#include <vector>

GLuint loadTexture(std::string filepath);
GLuint loadCubemap(std::vector<std::string> faces);

#endif
