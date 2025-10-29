
#ifndef COLOR_HPP_
#define COLOR_HPP_

#include <cstdint>
class Color {
public:
  Color();
  Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue,
        std::uint8_t alpha)
      : r(red), g(green), b(blue), a(alpha) {};
  ~Color() {};
  std::uint8_t r = 255;
  std::uint8_t g = 255;
  std::uint8_t b = 255;
  std::uint8_t a = 255;

  bool operator==(const Color &other) {
    if (this->r != other.r)
      return false;
    if (this->g != other.g)
      return false;
    if (this->b != other.b)
      return false;
    return true;
  }
};

#endif /* !COLOR_HPP_ */
