#include "bezierControlNetEffect.hpp"
#include "bezierPatch.hpp"
#include "bezierPatchEffect.hpp"
#include "bezierPatchGroup.hpp"
#include "orbitingCamera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include <algorithm>
#include <random>
#include <cstdlib>
#include <iostream>

using namespace std;

const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
float gRequestedScrolling = 0;

int gTessellationBump = 0;
bool gDisplayControlNet = false;
GLenum gPolygonMode = GL_FILL;

BezierPatchGroup *activePatch = nullptr;
BezierPatchGroup *unactivePatch = nullptr;

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  GLFWwindow *window = glfwCreateWindow(
      WIDTH, 
      HEIGHT, 
      "Tessellation", 
      nullptr, 
      nullptr
  );

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, key_callback);
  glfwSetScrollCallback(window, scroll_callback);

  glewExperimental = GL_TRUE;
  glewInit();

  random_device randomDevice;
  mt19937 generator(randomDevice());
  uniform_real_distribution<float> distribution(-1.0, 1.0);

  vector<float> heightmap;
  for (int z = 0; z < 3*4+1; ++z) {
    for (int x = 0; x < 3*4+1; ++x) {
      heightmap.push_back(distribution(generator));
    }
  }

  BezierPatchGroup patchWaves;
  patchWaves.createWavesExample();

  BezierPatchGroup patchSin;
  patchSin.createSinusoidalExample();

  activePatch = &patchWaves;
  unactivePatch = &patchSin;

  BezierPatchEffect bezierPatchEffect;
  bezierPatchEffect.initialize("bezierPatch");

  BezierControlNetEffect bezierNetEffect;
  bezierNetEffect.initialize("bezierPatchControlNet");

  glEnable(GL_DEPTH_TEST);

  OrbitingCamera camera;
  camera.setDist(7.0f);

  auto projection = glm::perspective(
    glm::radians(90.0f), (float)WIDTH/HEIGHT, 0.01f, 100.0f
  );

  double previousTime = glfwGetTime();
  double currentTime = glfwGetTime();
  double previousMousePositionX, previousMousePositionY;
  double currentMousePositionX, currentMousePositionY;
  double mouseSensitivityX = 0.01f;
  double mouseSensitivityY = 0.01f;
  glfwGetCursorPos(window, &currentMousePositionX, &currentMousePositionY);

  while (!glfwWindowShouldClose(window))
  {
      previousTime = currentTime;
      currentTime = glfwGetTime();
      double deltaTime = currentTime - previousTime;

      previousMousePositionX = currentMousePositionX;
      previousMousePositionY = currentMousePositionY;
      glfwGetCursorPos( window, &currentMousePositionX, 
          &currentMousePositionY
      );

      double mouseDeltaX = mouseSensitivityX * 
        (currentMousePositionX - previousMousePositionX);
      double mouseDeltaY = mouseSensitivityY * 
        (currentMousePositionY - previousMousePositionY);

      float distDelta = 0.05f * gRequestedScrolling;
      camera.setDist(fmax(1.0f, camera.getDist() + distDelta));
      gRequestedScrolling = 0.0f;

      if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        camera.rotate(mouseDeltaY, mouseDeltaX);
      }

      glfwPollEvents();
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glPolygonMode(GL_FRONT_AND_BACK, gPolygonMode);

      bezierPatchEffect.begin();
      bezierPatchEffect.setProjectionMatrix(projection);
      bezierPatchEffect.setViewMatrix(camera.getViewMatrix());
      bezierPatchEffect.setModelMatrix(glm::mat4(1.0f));
      bezierPatchEffect.setLightPosition(glm::vec3(0.0f, 4.0f, 0.0f));
      bezierPatchEffect.setTessellationLevelBump(gTessellationBump);
      activePatch->drawPatches(&bezierPatchEffect);
      bezierPatchEffect.end();

      if (gDisplayControlNet) {
        bezierNetEffect.begin();
        bezierNetEffect.setProjectionMatrix(projection);
        bezierNetEffect.setViewMatrix(camera.getViewMatrix());
        bezierNetEffect.setModelMatrix(glm::mat4(1.0f));
        activePatch->drawControlNets(&bezierNetEffect);
        bezierNetEffect.end();
      }

      glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}

void key_callback(
  GLFWwindow* window, 
  int key, 
  int scancode, 
  int action, 
  int mode
) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);

    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
      if (gPolygonMode == GL_FILL) gPolygonMode = GL_LINE;
      else gPolygonMode = GL_FILL;
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
      gDisplayControlNet = !gDisplayControlNet;
    }

    if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
      ++gTessellationBump;
    }

    if (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
      if (gTessellationBump > 0)
        --gTessellationBump;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
      swap(activePatch, unactivePatch);
    }
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
  gRequestedScrolling += yoffset;
}

