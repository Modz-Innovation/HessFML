/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include "IDrawable.hpp"
#include "Vector.hpp"
#include <vector>

namespace HessFML {
class Triangle : public IDrawable {
public:
  Triangle(Math::Vector3D v1, Math::Vector3D v2, Math::Vector3D v3);
  ~Triangle();
  
  void rotate(Math::Vector3D rotation) override;

  protected:
  void draw(const Window &window) const override;
  

private:
  Math::Vector3D vertex1;
  Math::Vector3D vertex2;
  Math::Vector3D vertex3;

  unsigned int vao_;
  unsigned int vbo_;

  std::vector<float> vertices_;
};
} // namespace HessFML

#endif /* !TRIANGLE_HPP_ */
