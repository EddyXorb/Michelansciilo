#pragma once

#include <functional>
#include <utility>

namespace michelansciilo {

enum class Align
{
    Left,
    Center
};

enum class Axis
{
    X,
    Z
};

struct Point2
{
    int x = 0;
    int z = 0;

    auto operator+(const Point2 r) const { return Point2{x + r.x, z + r.z}; }
    auto operator-(const Point2 r) const { return Point2{x - r.x, z - r.z}; }
    auto operator*(double scalar) const { return Point2{static_cast<int>(x * scalar), static_cast<int>(z * scalar)}; }
    bool operator==(const Point2& r) const { return x == r.x && z == r.z; }
};

struct Pixel
{
    Point2 p = Point2{0, 0};
    char c = '$';
};

struct Rectangle
{
    int x1 = 0;
    int z1 = 0;
    int x2 = 0;
    int z2 = 0;

    Rectangle() = default;
    Rectangle(Point2 origin, Point2 originOpposite) : x1(origin.x), x2(originOpposite.x), z1(origin.z), z2(originOpposite.z) {}
    Rectangle(int x1, int z1, int x2, int z2) : x1(x1), z1(z1), x2(x2), z2(z2) {}

    bool operator==(const Rectangle& r) const { return x1 == r.x1 && z1 == r.z1 && x2 == r.x2 && z2 == r.z2; }

    void operator+=(const Rectangle& r)
    {
        x1 = std::min(x1, r.x1);
        x2 = std::max(x2, r.x2);
        z1 = std::min(z1, r.z1);
        z2 = std::max(z2, r.z2);
    }

    auto getOrigin() const -> Point2 { return Point2{x1, z2}; }
    auto getOriginOpposite() const -> Point2 { return Point2{x2, z2}; }
    auto getDim() const -> Point2 { return Point2{x2 - x1, z2 - z1}; }
};

class Label;

struct DrawerCallback
{
    std::function<void(Pixel)> pixelDrawer;
    std::function<void(const Label&)> labelDrawer;
};

}  // namespace michelansciilo

// helper for hashing
template <class T>
inline constexpr void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
template <>
struct hash<michelansciilo::Point2>
{
    std::size_t operator()(const michelansciilo::Point2& v) const
    {
        std::size_t seed = 0;
        hash_combine(seed, v.x);
        hash_combine(seed, v.z);
        return seed;
    }
};
}  // namespace std
