/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Shader
*/

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include "Window.hpp"
#include <optional>
#include <string>

namespace HessFML {
enum SHADER_SINGLETON { SET = 0, GET = 1, DELETE = 2 };

enum SHADER_TYPE {
  NONE = -1,
  VERTEX_SHADER = GL_VERTEX_SHADER,
  FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
  GEOMETRY_SHADER = GL_FRAGMENT_SHADER,
  COMPUTE_SHADER = GL_COMPUTE_SHADER
};

class Shader {
public:
  Shader() {
    shaderId = -1;
    shaderType = NONE;
  };
  Shader(const std::string &shaderCode, enum SHADER_TYPE type);
  ~Shader() = default;

  int getShaderId(void) { return this->shaderId; }

  void setShaderId(int id) { this->shaderId = id; }

protected:
private:
  int shaderId;
  enum SHADER_TYPE shaderType;
};

Shader &defaultVertexShader(void);
Shader &defaultFragmentShader(void);

} // namespace HessFML

static const char *DEFAULT_VERTEX_SHADER =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

static const char *DEFAULT_FRAGMENT_SHADER =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\0";

#endif /* !SHADER_HPP_ */
