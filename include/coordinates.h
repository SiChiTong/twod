/**
 * @copyright 2018 TwoD
 * @author Brian Cairl
 *
 * @file coordinates.h
 */

#ifndef TWOD_COORDINATES_H
#define TWOD_COORDINATES_H

// C++ Standard Library
#include <tuple>

namespace twod
{

template<typename CoordT>
struct Coordinates
{
  CoordT x;
  CoordT y;

  constexpr Coordinates(CoordT _x, CoordT _y) :
    x{_x},
    y{_y}
  {}

  constexpr bool operator==(const Coordinates& other) const
  {
    return this->x == other.x and this->y == other.y;
  }

  constexpr bool operator!=(const Coordinates& other) const
  {
    return !this->operator==(other);
  }

  constexpr bool operator<(const Coordinates& other) const
  {
    return std::tie(this->x, this->y) < std::tie(other.x, other.y);
  }

  constexpr bool all_gt(const Coordinates& other) const
  {
    return this->x > other.x and
           this->y > other.y;
  }

  constexpr bool all_ge(const Coordinates& other) const
  {
    return this->x >= other.x and
           this->y >= other.y;
  }

  constexpr bool all_lt(const Coordinates& other) const
  {
    return this->x < other.x and
           this->y < other.y;
  }

  constexpr bool all_le(const Coordinates& other) const
  {
    return this->x <= other.x and
           this->y <= other.y;
  }

  constexpr int area() const
  {
    return x * y;
  }

  constexpr static Coordinates Zero()
  {
    return Coordinates{0, 0};
  }

  friend constexpr Coordinates operator-(const Coordinates lhs, const Coordinates rhs)
  {
    return Coordinates{lhs.x - rhs.x, lhs.y - rhs.y};
  }

  friend constexpr Coordinates operator+(const Coordinates lhs, const Coordinates rhs)
  {
    return Coordinates{lhs.x + rhs.x, lhs.y + rhs.y};
  }
};

}  // namespace twod

#endif // TWOD_COORDINATES_H