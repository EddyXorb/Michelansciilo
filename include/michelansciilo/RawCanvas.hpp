#pragma once
#include <unordered_map>

#include <michelansciilo/TinyStructs.hpp>
namespace michelansciilo {

struct Pixel;
class A_SpecialDrawer;
class Settings;

class RawCanvas
{
 public:
    static constexpr char EMPTY_CHAR = ' ';

    RawCanvas(const Settings& settings) : settings_(settings){};

    auto get(Point2 p) const -> char;

    void set(Pixel p);

    auto print() const -> std::string;
    void clear();

 private:
    Rectangle borders_;
    const Settings& settings_;
    std::unordered_map<Point2, char> canvas_;

    auto scalePoint(Point2 p) const -> Point2;
};

}  // namespace michelansciilo
