#version 400 core
layout(quads) in;

in vec3 tcPosition[];
out vec3 tePosition;
out vec4 tePatchDistance;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
  float u = gl_TessCoord.x, v = gl_TessCoord.y;
  vec3 a = mix(tcPosition[0], tcPosition[3], u);
  vec3 b = mix(tcPosition[12], tcPosition[15], u);
  tePosition = mix(a, b, v);
  tePatchDistance = vec4(u, v, 1-u, 1-v);
  gl_Position = projectionMatrix * viewMatrix * modelMatrix
    * vec4(tePosition, 1);
}
