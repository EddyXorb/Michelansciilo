#include "michelansciilo/Drawer.hpp"
#include "michelansciilo/TinyStructs.hpp"

using namespace michelansciilo;

auto Drawer::print() -> std::string
{
    DrawerCallback borderTestCallbacks;

    borderTestCallbacks.labelDrawer = [this](const Label& l) {
        int startX = l.getAlign() == Align::Left ? l.getPos().x : l.getPos().x - static_cast<int>(l.size()) / 2;
        int endX = startX + static_cast<int>(l.size());
        int z = l.getPos().z;
        auto bounding = Rectangle(startX, z, endX, z);

        if (bound_ == Rectangle(0, 0, 0, 0))
            bound_ = bounding;
        else
            bound_ += bounding;
    };

    borderTestCallbacks.pixelDrawer = [this](Pixel p) {
        auto bounding = Rectangle(p.p.x, p.p.z, p.p.x, p.p.z);

        if (bound_ == Rectangle(0, 0, 0, 0))
            bound_ = bounding;
        else
            bound_ += bounding;
    };

    for (const auto& drawer : generalDrawer_)
    {
        drawer->draw(borderTestCallbacks);
    }

    DrawerCallback scaledCallbacks;

    scaledCallbacks.labelDrawer = [this](const Label& l) {
        int xOffset = l.getAlign() == Align::Center ? -(static_cast<int>(l.size()) / 2) : 0;

        auto pos = getScaledAndShiftedPoint(l.getPos());

        for (const auto& c : l.getText())
        {
            canvas_.set(Pixel{pos.x + xOffset++, pos.z, c});
        }
    };

    scaledCallbacks.pixelDrawer = [this](Pixel p) {
        auto scaled = getScaledAndShiftedPoint(Point2{p.p.x, p.p.z});

        canvas_.set(Pixel{scaled.x, scaled.z, p.c});
    };

    for (const auto& drawer : generalDrawer_)
    {
        drawer->draw(scaledCallbacks);
    }

    return canvas_.print();
}

auto Drawer::clear()
{
    generalDrawer_.clear();
    canvas_.clear();
    bound_ = Rectangle{0, 0, 0, 0};
}

// shift canvas into origin and scale it
auto Drawer::getScaledAndShiftedPoint(Point2 p) const -> Point2
{
    Point2 origin = bound_.getOrigin();
    if (settings_.mirror_.find(Axis::X) != settings_.mirror_.end())
    {
        origin.x = bound_.x2;
        p.x = bound_.x2 - p.x;
    }
    if (settings_.mirror_.find(Axis::Z) != settings_.mirror_.end())
    {
        origin.z = bound_.z2;
        p.z = bound_.z2 - p.z;
    }

    return (p - bound_.getOrigin()) * settings_.scalefactor_;
}
