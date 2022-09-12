#pragma once
#include <functional>
#include <string>
#include <vector>
#include <memory>

#include "michelansciilo/Settings.hpp"
#include "michelansciilo/SpecialDrawer.hpp"
#include "michelansciilo/RawCanvas.hpp"

namespace michelansciilo {

class Label;

class Drawer
{
 public:
    Drawer(Settings settings = Settings()) : settings_(settings), canvas_(this->settings_){};

    template <class SpecialDrawer>
    auto add(SpecialDrawer drawer) -> Drawer&;

    auto print() -> std::string;
    auto clear();

 private:
    Settings settings_;
    std::vector<std::unique_ptr<A_SpecialDrawer>> generalDrawer_;
    RawCanvas canvas_;
    Rectangle bound_ = Rectangle();

    auto getScaledAndShiftedPoint(Point2 p) const -> Point2;
};

template <class SpecialDrawer>
auto Drawer::add(SpecialDrawer drawer) -> Drawer&
{
    static_assert(std::is_base_of<A_SpecialDrawer, SpecialDrawer>::value, "SpecialDrawer need to be derived from A_SpecialDrawer");
    generalDrawer_.emplace_back(std::make_unique<SpecialDrawer>(std::move(drawer)));
    return *this;
}

}  // namespace michelansciilo
