/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Shader
*/

#include "Shader.hpp"
#include "Window.hpp"

namespace HessFML {

Shader &defaultVertexShader(void) {
    static Shader vertexShader(DEFAULT_VERTEX_SHADER, VERTEX_SHADER);

    return vertexShader;
}

Shader &defaultFragmentShader(void) {
    static Shader fragmentShader(DEFAULT_FRAGMENT_SHADER, FRAGMENT_SHADER);

    return fragmentShader;
}

Shader::Shader(const std::string &shaderCode, enum SHADER_TYPE type)
    : shaderId(0), shaderType(type) {
  this->shaderId = glCreateShader(type);
  const char *source = shaderCode.c_str();
  glShaderSource(this->shaderId, 1, &source, NULL);
  glCompileShader(this->shaderId);
}

} // namespace HessFML
