#pragma once
#include <set>

#include <michelansciilo/TinyStructs.hpp>

namespace michelansciilo {

class Drawer;

class Settings
{
 public:
    auto mirror(std::set<Axis> axes) -> Settings&;  // unimplemented
    auto scale(double scalefactor) -> Settings&;    //
    auto printAxis() -> Settings&;                  // unimplemented
    auto printOrigin() -> Settings&;                // unimplemented

 private:
    friend class Drawer;
    friend class RawCanvas;

    std::set<Axis> mirror_;
    double scalefactor_ = 1.0;
    bool printAxis_ = false;
    bool printOrigin_ = false;
};
}  // namespace michelansciilo