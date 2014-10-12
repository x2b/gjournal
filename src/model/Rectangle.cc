#include "Rectangle.hh"

Rectangle::Rectangle()
  : x(0), y(0),
    width(-1),
    height(-1)
{
}

double Rectangle::getX() const
{
  return x;
}

double Rectangle::getY() const
{
  return y;
}

double Rectangle::getWidth() const
{
  return width;
}

double Rectangle::getHeight() const
{
  return height;
}

bool Rectangle::isValid() const
{
  return getWidth() >= 0 && getHeight() >= 0;
}
