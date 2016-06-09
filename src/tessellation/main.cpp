#include <algorithm>
#include <random>
#include <cstdlib>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

#include "bezierPatch.hpp"
#include "bezierPatchEffect.hpp"
#include "orbitingCamera.hpp"

const GLuint WIDTH = 800, HEIGHT = 600;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

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

  BezierPatch patch;
  patch.createFlatGrid(10.0f, 10.0f);

  BezierPatchEffect bezierPatchEffect;
  bezierPatchEffect.initialize("bezierPatch");

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  OrbitingCamera camera;
  camera.rotate(glm::radians(30.0f), glm::radians(45.0f));
  camera.setDist(7.0f);

  auto projection = glm::perspective(
    glm::radians(90.0f), (float)WIDTH/HEIGHT, 0.1f, 100.0f
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

      if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        camera.rotate(-mouseDeltaY, mouseDeltaX);
      }

      glfwPollEvents();
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      bezierPatchEffect.begin();
      bezierPatchEffect.setProjectionMatrix(projection);
      bezierPatchEffect.setViewMatrix(camera.getViewMatrix());
      bezierPatchEffect.setModelMatrix(glm::mat4(1.0f));
      patch.drawPatch();
      bezierPatchEffect.end();

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
    )
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
}

