#version 400 core

out vec4 color;

in vec3 teNormal;
in vec3 teLightDirection;

void main() {
  float diffuse = clamp(dot(normalize(teNormal), teLightDirection), 0, 1);
  color = vec4(diffuse, diffuse, diffuse, 1);
}
