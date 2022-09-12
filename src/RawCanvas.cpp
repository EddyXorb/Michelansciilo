#include <sstream>

#include "michelansciilo/RawCanvas.hpp"
#include "michelansciilo/Drawer.hpp"
#include "michelansciilo/TinyStructs.hpp"

using namespace michelansciilo;

auto RawCanvas::get(Point2 p) const -> char
{
    auto it = canvas_.find(p);
    if (it == canvas_.end())
        return EMPTY_CHAR;
    return it->second;
}

void RawCanvas::set(Pixel p)
{
    auto point = p.p;

    if (!canvas_.empty())
    {
        auto& b = borders_;
        b.x1 = std::min(p.p.x, b.x1);
        b.z1 = std::min(p.p.z, b.z1);
        b.x2 = std::max(p.p.x, b.x2);
        b.z2 = std::max(p.p.z, b.z2);
    }
    else
        borders_ = Rectangle(point, point);

    canvas_[point] = p.c;
}

auto RawCanvas::print() const -> std::string
{
    auto origin = borders_.getOrigin();
    auto oppositeOrigin = borders_.getOriginOpposite();

    std::stringstream ss;

    ss << "\n";
    for (int z = origin.z; z <= oppositeOrigin.z; ++z)
    {
        for (int x = origin.x; x <= oppositeOrigin.x; ++x)
        {
            ss << this->get(Point2{x, z});
        }
        ss << "\n";
    }

    return ss.str();
}

void RawCanvas::clear()
{
    canvas_.clear();
    borders_ = Rectangle();
}

auto RawCanvas::scalePoint(Point2 p) const -> Point2
{
    auto origin = borders_.getOrigin();
    return (p - origin) * settings_.scalefactor_;
}
