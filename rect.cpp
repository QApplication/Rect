#include "rect.h"


gui::Rect::Rect(int x, int y, int width, int height)
    : mX1(x), mX2(x + width - 1), mY1(y), mY2(y + height - 1)
{

}

gui::Rect::Rect(const std::pair<int, int> &topLeft, const std::pair<int, int> &size)
    : Rect(std::get<0>(topLeft), std::get<1>(topLeft), std::get<0>(size), std::get<1>(size))
{

}

gui::Rect::Rect()
    : Rect(0, 0, -1, -1)    // not valid by default
{

}

gui::Rect::Rect(const Rect &other)
{
    copy(other);
}

gui::Rect &gui::Rect::operator=(Rect &other)
{
    if (this != &other)
        copy(other);
    return *this;
}

gui::Rect &gui::Rect::operator=(Rect &&other)
{
    if (this != &other) {
        mX1 = std::move(other.mX1);
        mX2 = std::move(other.mX2);
        mY1 = std::move(other.mY1);
        mY2 = std::move(other.mY2);
    }
    return *this;
}

gui::Rect::Rect(Rect &&other)
{
    mX1 = std::move(other.mX1);
    mX2 = std::move(other.mX2);
    mY1 = std::move(other.mY1);
    mY2 = std::move(other.mY2);
}

bool gui::Rect::valid() const
{
    return (mX1 < mX2) && (mY1 < mY2);
}

int gui::Rect::width() const
{
    return  mX2 - mX1 + 1;
}

void gui::Rect::setWidth(int width)
{
    mX2 = mX1 + width - 1;
}

int gui::Rect::height() const
{
    return mY2 - mY1 + 1;
}

void gui::Rect::setHeight(int height)
{
    mY2 = mY1 + height - 1;
}

int gui::Rect::x() const
{
    return mX1;
}

void gui::Rect::setX(int x)
{
    mX1 = x;
}

int gui::Rect::y() const
{
    return mY1;
}

void gui::Rect::setY(int y)
{
    mY1 = y;
}

int &gui::Rect::left()
{
    return mX1;
}

int gui::Rect::left() const
{
    return mX1;
}

void gui::Rect::setLeft(int pos)
{
    mX1 = pos;
}

int &gui::Rect::top()
{
    return mY1;
}

int gui::Rect::top() const
{
    return mY1;
}

void gui::Rect::setTop(int pos)
{
    mY1 = pos;
}

int &gui::Rect::right()
{
    return mX2;
}

int gui::Rect::right() const
{
    return mX2;
}

void gui::Rect::setRight(int pos)
{
    mX2 = pos;
}

int &gui::Rect::bottom()
{
    return mY2;
}

int gui::Rect::bottom() const
{
    return mY2;
}

void gui::Rect::setBottom(int pos)
{
    mY2 = pos;
}

std::pair<int, int> gui::Rect::topLeft() const
{
    return {mX1, mY1};
}

void gui::Rect::setTopLeft(const std::pair<int, int> &p)
{
    mX1 = std::get<0>(p);
    mY1 = std::get<1>(p);
}

std::pair<int, int> gui::Rect::bottomRight() const
{
    return {mX2, mY2};
}

void gui::Rect::setBottomRight(const std::pair<int, int> &p)
{
    mX2 = std::get<0>(p);
    mY2 = std::get<1>(p);
}

std::pair<int, int> gui::Rect::topRight() const
{
    return {mX2, mY1};
}

void gui::Rect::setTopRight(const std::pair<int, int> &p)
{
    mX2 = std::get<0>(p);
    mY1 = std::get<1>(p);
}

std::pair<int, int> gui::Rect::bottomLeft() const
{
    return {mX1, mY2};
}

void gui::Rect::setBottomLeft(const std::pair<int, int> &p)
{
    mX1 = std::get<0>(p);
    mY2 = std::get<1>(p);
}

void gui::Rect::inflate(int dx, int dy)
{
    mX1 -= dx;
    mX2 += dx;
    mY1 -= dy;
    mY2 += dy;
}

std::pair<int, int> gui::Rect::center() const
{
    return {(mX1 + mX2)/2, (mY1 + mY2)/2};
}

std::pair<int, int> gui::Rect::size() const
{
    return {width(), height()};
}

void gui::Rect::rotate(double angle)
{

}

void gui::Rect::copy(const Rect &r)
{
    mX1 = r.mX1;
    mX2 = r.mX2;
    mY1 = r.mY1;
    mY2 = r.mY2;
}
