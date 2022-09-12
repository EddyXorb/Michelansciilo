
#pragma once

#include <string>

#include <michelansciilo/TinyStructs.hpp>

namespace michelansciilo {

class A_SpecialDrawer
{
 public:
    virtual ~A_SpecialDrawer(){};

    void draw(DrawerCallback callback);

 protected:
    virtual void draw_() = 0;

    DrawerCallback callback_;
};

class Line : public A_SpecialDrawer
{
 public:
    static constexpr char symbol_horizontal = '-';
    static constexpr char symbol_vertical = '|';

    Line(Point2 start, int length, Axis axis, char startSymbol = ' ', char endSymbol = ' ') : start_(start), axis_(axis), length_(length) {}

 protected:
    void draw_() override;

 private:
    Point2 start_;
    Axis axis_;
    int length_;
    char startSymbol_ = ' ';
    char endSymbol_ = ' ';
};

class Rect : public A_SpecialDrawer
{
 public:
    static constexpr char edges = 'o';

    Rect(Rectangle rec, std::string caption = "") : rec_(rec), caption_(std::move(caption)) {}

 protected:
    void draw_() override;

 private:
    Rectangle rec_;
    std::string caption_;
};

// Don't use this to print readable labels as this drawers results get scaled and text may be overwritten because of that, resulting in
// unreadable text
class GenericText : public A_SpecialDrawer
{
 public:
    GenericText(Point2 start, std::string text, Axis axis = Axis::X) : text_(std::move(text)), start_(start), axis_(axis) {}

 protected:
    void draw_() override;

 private:
    std::string text_;
    Point2 start_;
    Axis axis_;
};

// This is merely a container without much logic. The logic is given by callback-defining side drawer for the label case.
class Label : public A_SpecialDrawer
{
 public:
    Label(Point2 pos, std::string text, Align align = Align::Center) : text_(std::move(text)), pos_(pos), align_(align) {}

    auto size() const { return text_.size(); }
    auto getText() const -> std::string { return text_; }
    auto getPos() const -> Point2 { return pos_; }
    auto getAlign() const -> Align { return align_; }

 protected:
    void draw_() override;

 private:
    std::string text_;
    Point2 pos_;
    Align align_;
};
}  // namespace michelansciilo