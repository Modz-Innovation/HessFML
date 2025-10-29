/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** Camera
*/

#include "Camera.hpp"
#include "Window.hpp"
#include <cmath>

namespace HessFML {
Camera::Camera() {
    this->pos_ = Math::Vector3D(0.0f, 0.0f, 3.0f);
    this->target_ = Math::Vector3D(0.0f, 0.0f, 0.0f);
    this->up_ = Math::Vector3D(0.0f, 1.0f, 0.0f);
    this->fov_ = 45.0;
    this->near_ = 0.1;
    this->far_ = 100.0;
}

Camera::Camera(const Math::Vector3D &position, const Math::Vector3D &target) 
    : pos_(position), target_(target), up_(Math::Vector3D(0.0f, 1.0f, 0.0f)), fov_(45.0), near_(0.1), far_(100.0) {
}

Math::Vector3D Camera::getDirection() const {
    return pos_ - target_;
}

Math::Matrix<float> Camera::getViewMatrix() const {
    return Math::Matrix<float>(4, 4).lookAt(pos_, target_, up_);
}

Math::Matrix<float> Camera::getProjectionMatrix(const Window &window) const {
    Math::Matrix<float> p(4, 4);
    p = p.identity();
    
    float aspectRatio = static_cast<float>(window.getWidth()) / static_cast<float>(window.getHeight());
    float contangent = 1.0 / std::tan((this->fov_ / 2.0) * (M_PI / 180.0));
    p.data_[0][0] = contangent / aspectRatio;
    p.data_[1][1] = contangent;
    p.data_[2][2] = -far_  / (far_ - near_);
    p.data_[2][3] = -far_ * near_ / (far_ - near_);
    p.data_[3][2] = -1.0;
    p.data_[3][3] = 0.0;
    return p;
}

Camera::~Camera() {}

} // namespace HessFML