/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Vector.hpp"
#include "Window.hpp"

namespace HessFML {

Triangle::Triangle(Math::Vector3D v1, Math::Vector3D v2, Math::Vector3D v3)
    : vertex1(v1), vertex2(v2), vertex3(v3) {

  this->vertices_.insert(this->vertices_.end(),
                         {(float)vertex1.x, (float)vertex1.y, (float)vertex1.z,
                          (float)vertex2.x, (float)vertex2.y, (float)vertex2.z,
                          (float)vertex3.x, (float)vertex3.y, (float)vertex3.z});

  glGenVertexArrays(1, &this->vao_);
  glGenBuffers(1, &this->vbo_);
  glBindVertexArray(this->vao_);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
  glBufferData(GL_ARRAY_BUFFER, this->vertices_.size() * sizeof(float),
               this->vertices_.data(), GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindVertexArray(0);
}

void Triangle::draw(const Window &window) const {
  glUseProgram(window.getShaderProgram());
  glBindVertexArray(this->vao_);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::rotate(Math::Vector3D rotation) {
    this->vertex1.rotateX(rotation.x);
    this->vertex2.rotateX(rotation.x);
    this->vertex3.rotateX(rotation.x);
    this->vertex1.rotateY(rotation.y);
    this->vertex2.rotateY(rotation.y);
    this->vertex3.rotateY(rotation.y);
    this->vertex1.rotateZ(rotation.z);
    this->vertex2.rotateZ(rotation.z);
    this->vertex3.rotateZ(rotation.z);
    this->vertices_.clear();
    this->vertices_.insert(this->vertices_.end(),
                         {(float)vertex1.x, (float)vertex1.y, (float)vertex1.z,
                          (float)vertex2.x, (float)vertex2.y, (float)vertex2.z,
                          (float)vertex3.x, (float)vertex3.y, (float)vertex3.z});
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo_);
    glBufferData(GL_ARRAY_BUFFER, this->vertices_.size() * sizeof(float),
               this->vertices_.data(), GL_STATIC_DRAW);
}

Triangle::~Triangle() {
  glDeleteVertexArrays(1, &this->vao_);
  glDeleteBuffers(1, &this->vbo_);
}
} // namespace HessFML
