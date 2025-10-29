/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#include "Color.hpp"
#include "IDrawable.hpp"
#include "Triangle.hpp"

namespace HessFML {
class Window {
public:
  class WindowException : public std::exception {
    const char *what() const noexcept override {
      return "Window initialization failed";
    }
  };

public:
  Window(std::size_t width = 800, std::size_t height = 600,
         const std::string &title = "HessFML Window");
  ~Window();

  unsigned int getShaderProgram() const { return this->shaderProgram; }
  size_t getWidth() const { return this->width_; }
  size_t getHeight() const { return this->height_; }

  friend IDrawable;

  bool shouldClose(void) const { return glfwWindowShouldClose(this->window_); }
  void swapBuffers(void) { glfwSwapBuffers(this->window_); }
  void clear(const Color &color) {
    glClearColor(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f,
                 color.a / 255.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
  void pollEvents(void) { glfwPollEvents(); }
  void update(void);
  void draw(const IDrawable &drawable);

private:
  size_t width_;
  size_t height_;
  unsigned int shaderProgram;
  std::string title_;
  GLFWwindow *window_;
};

class GLFWInitException : public Window::WindowException {
  const char *what() const noexcept override {
    return "GLFW initialization failed";
  }
};

class WindowCreationException : public Window::WindowException {
  const char *what() const noexcept override {
    return "Window creation failed";
  }
};

class GLADLoadException : public Window::WindowException {
  const char *what() const noexcept override {
    return "GLAD loader initialization failed";
  }
};

} // namespace HessFML

#endif /* !WINDOW_HPP_ */
