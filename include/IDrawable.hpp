/*
** EPITECH PROJECT, 2025
** 3DOpenGL
** File description:
** IDrawable
*/

#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include <Vector.hpp>

namespace HessFML {

    class Window;

    class IDrawable {
        public:
            virtual void draw(const Window &window) const = 0;
            virtual void rotate(Math::Vector3D roaion) = 0;
        protected:
        private:
    };
}

#endif /* !IDRAWABLE_HPP_ */
