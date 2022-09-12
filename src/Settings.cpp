#include "michelansciilo/Settings.hpp"

namespace michelansciilo {

auto Settings::mirror(std::set<Axis> axes) -> Settings&
{
    mirror_ = axes;
    return *this;
};

auto Settings::scale(double scalefactor) -> Settings&
{
    scalefactor_ = scalefactor;
    return *this;
}

auto Settings::printAxis() -> Settings&
{
    printAxis_ = true;
    return *this;
}

auto Settings::printOrigin() -> Settings&
{
    printOrigin_ = true;
    return *this;
}

}  // namespace michelansciilo