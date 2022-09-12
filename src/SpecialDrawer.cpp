#include "michelansciilo/SpecialDrawer.hpp"

namespace michelansciilo {

void A_SpecialDrawer::draw(DrawerCallback callback)
{
    callback_ = callback;
    draw_();
}

void Rect::draw_()
{
    auto dim = rec_.getDim();
    Line(rec_.getOrigin(), dim.x, Axis::X, edges, edges).draw(callback_);
    Line(rec_.getOrigin(), dim.z, Axis::Z, edges, edges).draw(callback_);
    Line(rec_.getOrigin() + Point2{dim.x, 0}, dim.z, Axis::Z, edges, edges).draw(callback_);
    Line(rec_.getOrigin() + Point2{0, dim.z}, dim.x, Axis::X, edges, edges).draw(callback_);

    if (!caption_.empty())
    {
        auto halfDim = dim * 0.5;
        auto middle = rec_.getOrigin() + Point2{halfDim.x, halfDim.z};

        Label(middle, caption_, Align::Center).draw(callback_);
    }
}

void GenericText::draw_()
{
    auto cnt = 0;
    for (const auto& c : text_)
    {
        Pixel p{start_.x, start_.z, c};

        if (axis_ == Axis::X)
            p.p.x += cnt++;
        else
            p.p.z += start_.z + cnt++;

        callback_.pixelDrawer(p);
    }
}

void Label::draw_()
{
    callback_.labelDrawer(*this);
}

void Line::draw_()
{
    bool alongZ = axis_ == Axis::Z;
    auto end = alongZ ? start_.z + length_ : start_.x + length_;

    for (auto i = alongZ ? start_.z : start_.x; i <= end; ++i)
    {
        int x = alongZ ? start_.x : i;
        int z = alongZ ? i : start_.z;
        char c = axis_ == Axis::X ? symbol_horizontal : symbol_vertical;

        callback_.pixelDrawer(Pixel{x, z, c});
    }

    if (startSymbol_ != ' ')
        callback_.pixelDrawer(Pixel{start_.x, start_.z, startSymbol_});
    if (endSymbol_ != ' ')
        callback_.pixelDrawer(Pixel{alongZ ? start_.x : end, alongZ ? end : start_.z, endSymbol_});
}

}  // namespace michelansciilo