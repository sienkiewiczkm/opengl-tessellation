#version 400 core

layout (location = 0) in vec3 position;
in vec3 teNormal;
out vec3 vPosition;

void main() {
  vPosition = position.xyz;
}
