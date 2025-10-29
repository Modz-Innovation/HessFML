/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "Matrix.hpp"
#include "Vector.hpp"
#include "Window.hpp"
namespace HessFML {
class Camera {
public:
  Camera();
  Camera(const Math::Vector3D &position, const Math::Vector3D &target);
  ~Camera();

  Math::Vector3D getPosition() const { return pos_; }
  Math::Vector3D getUp() const { return up_; }
  Math::Vector3D getTarget() const { return target_; }
  double getFov() const { return fov_; }
  double getNear() const { return near_; }
  double getFar() const { return far_; }

  void setPosition(const Math::Vector3D &position) { pos_ = position; }
  void setUp(const Math::Vector3D &up) { up_ = up; }
  void setTarget(const Math::Vector3D &target) { target_ = target; }
  void setFov(double fov) { fov_ = fov; }
  void setNear(double near) { near_ = near; }
  void setFar(double far) { far_ = far; }

  Math::Vector3D getDirection() const;
  Math::Matrix<float> getViewMatrix() const;
  Math::Matrix<float> getProjectionMatrix(const Window &window) const;

protected:
  Math::Vector3D pos_;
  Math::Vector3D target_;
  Math::Vector3D up_;

  double fov_;
  double near_;
  double far_;
};
} // namespace HessFML

#endif /* !CAMERA_HPP_ */
