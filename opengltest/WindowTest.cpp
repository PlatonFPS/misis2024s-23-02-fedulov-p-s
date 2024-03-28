#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader/shader.hpp>
#include <numbers>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
  std::cout << "User resized window to " << width << "x" << height << '\n';
}

float xOffset = 0;
float yOffset = 0;
float stepOffset = 0.005f;
float maxABSValue = 3.0f;

float xScroll = 0.5f;
float yScroll = 0.0f;
float scrollMultiplier = 0.025f;
float deltaTime;

float radius = 5.0f;

float yaw = 1.5f * std::numbers::pi;
float pitch = std::numbers::pi;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
glm::vec3 cameraDirection;
glm::vec3 cameraUp;
glm::vec3 cameraRight;
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
const float cameraSpeed = 10.0f;

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
    std::cout << "User closed the application" << '\n';
  }
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    xOffset -= stepOffset;
    cameraPos -= deltaTime * cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraDirection));
  }
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    xOffset += stepOffset;
    cameraPos += deltaTime * cameraSpeed * glm::normalize(glm::cross(cameraUp, cameraDirection));
  }
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    yOffset -= stepOffset;
    cameraPos += deltaTime * cameraSpeed * cameraDirection;
  }
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    yOffset += stepOffset;
    cameraPos -= deltaTime * cameraSpeed * cameraDirection;
  }
  if (xOffset > maxABSValue) xOffset = maxABSValue;
  if (xOffset < -maxABSValue) xOffset = -maxABSValue;
  if (yOffset > maxABSValue) yOffset = maxABSValue;
  if (yOffset < -maxABSValue) yOffset = -maxABSValue;
}

void ClearWindow() {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DebugColor(float time) {
  float pi = 3.141592653589793;
  float phaseX = (sin(time + pi) / 2.0) + 0.5;
  float phaseY = (sin(time + pi * (2 / 3)) / 2.0) + 0.5;
  float phaseZ = (sin(time + pi * (4 / 3)) / 2.0) + 0.5;
  std::cout << phaseX << " " << phaseY << " " << phaseZ << '\n';
}

void clamp(float& value) {
  if (value < -1.0) value = 1.0f;
  if (value > 1.0) value = -1.0f;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
  yScroll -= yoffset * scrollMultiplier;
  xScroll += xoffset * scrollMultiplier;
  clamp(xScroll);
  clamp(yScroll);
  yaw = (xScroll + 1) * std::numbers::pi;
  pitch = (yScroll + 1) * std::numbers::pi;
  std::cout << (xScroll + 1) * 180 << "|" << (yScroll + 1) * 180 << '\n';
}

int main() {
  std::string prefix = std::filesystem::current_path().string() + "/../../../../../../opengltest/";

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << '\n';
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  { 
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  glfwSetScrollCallback(window, scroll_callback);

  float vertices[] = {
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left front 
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left front 
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right front 
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left front 
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, // top right front
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right front 

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left back
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left back 
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right back 
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left back 
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right back
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right back

    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left right
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left right
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right right
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right right
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right right

    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left left
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left left
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right left
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // top left left
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right left
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right left

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left up
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, // bottom left up
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom right up
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top left up
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top right up
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, // bottom right up

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left bottom
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom left bottom
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right bottom
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left bottom
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top right bottom
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom right bottom
  };

  std::vector<glm::vec3> cubePositions{
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.0f, 1.0f, -2.0f),
    glm::vec3(-1.0f, 1.0f, -3.0f),
    glm::vec3(1.0f, -1.0f, 3.0f),
    glm::vec3(-1.0f, -1.0f, -5.0f),
  };

  /*
  03 47
  12 56
  */

  unsigned int indices[] = {
    0, 1, 2, //front lower
    0, 2, 3, //front upper
    4, 5, 6, //back lower
    4, 6, 7, //back upper
    2, 3, 6, //right lower
    3, 7, 6, //right upper
    4, 5, 1, //left lower
    4, 0, 1, //left upper
    4, 0, 3, //top lower
    4, 7, 3, //top upper
    1, 5, 6, //bottom lower
    1, 2, 6, //bottom upper
  };

  float TexCoords[] = {
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f
  };

  //light setup
  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
  glm::vec3 cubeColor(1.0f, 1.0f, 1.0f);
  glm::vec3 result = lightColor * cubeColor;

  glm::vec3 lightPos(0.0f, 3.0f, 0.0f);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  stbi_set_flip_vertically_on_load(true);

  int width, height, nrChannels;
  std::string s_texture = prefix + "test.png";
  unsigned char* data = stbi_load(s_texture.c_str(), &width, &height,&nrChannels, 0);
  unsigned int texture1;
  glGenTextures(1, &texture1);

  glActiveTexture(GL_TEXTURE0); 
  glBindTexture(GL_TEXTURE_2D, texture1);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //vertex position
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  //vertex texture
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  //light source setup
  unsigned int lightVAO;
  glGenVertexArrays(1, &lightVAO);
  glBindVertexArray(lightVAO);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  std::string vert = prefix + "shaders/SimpleShader.vert";
  std::string frag = prefix + "shaders/SimpleShader.frag";
  
  Shader shader(vert.c_str(), frag.c_str());

  vert = prefix + "shaders/LightSource.vert";
  frag = prefix + "shaders/LightSource.frag";

  Shader lightShader(vert.c_str(), frag.c_str());

  glEnable(GL_DEPTH_TEST);

  float lastTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    ClearWindow();

    deltaTime = glfwGetTime() - lastTime;
    lastTime = glfwGetTime();

    //input
    processInput(window);
    
    //cube render
    shader.Bind();
    shader.SetInt("texture1", 0);
    shader.SetVec3("lightColor", lightColor);
    shader.SetVec3("objectColor", cubeColor);

    cameraDirection.x = cos(yaw) * cos(pitch);
    cameraDirection.y = sin(pitch);
    cameraDirection.z = sin(yaw) * cos(pitch);

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    cameraUp = glm::cross(cameraDirection, cameraRight);

    glm::mat4 view = glm::lookAt(cameraPos, cameraPos - cameraDirection, cameraUp);
    shader.SetMat4("view", view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.SetMat4("projection", projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBindVertexArray(VAO);

    for (glm::vec3 position : cubePositions) {
      glm::mat4 model = glm::mat4(1.0f);

      model = glm::translate(model, position);

      shader.SetMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    shader.UnBind();

    //drawing light source
    lightShader.Bind();
    lightShader.SetVec3("lightColor", lightColor);

    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.5f));

    lightShader.SetMat4("model", lightModel);
    lightShader.SetMat4("view", view);
    lightShader.SetMat4("projection", projection);

    glBindVertexArray(lightVAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);

    lightShader.UnBind();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}