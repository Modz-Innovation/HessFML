/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Window
*/

#include "Window.hpp"
#include "Shader.hpp"
#include <iostream>

namespace HessFML {

Window::Window(std::size_t width, std::size_t height, const std::string &title)
    : width_(width), height_(height), title_(title) {
  if (!glfwInit())
    throw GLFWInitException();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  this->window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (!this->window_) {
    glfwTerminate();
    throw WindowCreationException();
  }
  glfwMakeContextCurrent(this->window_);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(this->window_);
    throw GLADLoadException();
  }
  glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
  glfwSetFramebufferSizeCallback(this->window_,
                                 [](GLFWwindow *, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });
  this->shaderProgram = glCreateProgram();

  glAttachShader(this->shaderProgram, defaultVertexShader().getShaderId());
  glAttachShader(this->shaderProgram, defaultFragmentShader().getShaderId());
  glLinkProgram(this->shaderProgram);
}

void Window::update(void) {
    glfwPollEvents();
    this->swapBuffers();
}

void Window::draw(const IDrawable &drawable) {
  drawable.draw(*this);
}

Window::~Window() {
  if (this->window_) {
    glfwDestroyWindow(this->window_);
  }
  glfwTerminate();
}
} // namespace HessFML
