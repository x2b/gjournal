#include "Rectangle.hh"

#include "util/Error.hh"

Rectangle::Rectangle()
  : x(0), y(0),
    width(-1),
    height(-1)
{
}

Rectangle::Rectangle(double x_,
		     double y_,
		     double width_,
		     double height_)
  : x(x_), y(y_), width(width_), height(height_)
{
}

Rectangle::Rectangle(const Gdk::Rectangle& rect)
  : Rectangle(rect.get_x(), rect.get_y(),
              rect.get_width(),
              rect.get_height())
{
}


double Rectangle::get_x() const
{
  return x;
}

double Rectangle::get_y() const
{
  return y;
}

double Rectangle::get_width() const
{
  return width;
}

double Rectangle::get_height() const
{
  return height;
}

bool Rectangle::intersects(const Rectangle& other) const
{
  gj_assert(is_valid() and other.is_valid());

  return
    get_x() <= other.get_x() + other.get_width() and
    other.get_x() <= get_x() + get_width() and
    get_y() <= other.get_y() + other.get_height() and
    other.get_y() <= get_y() + get_height();
}

Rectangle Rectangle::intersect(const Rectangle& other) const
{
  gj_assert(is_valid() and other.is_valid());

  double xval = std::max(get_x(), other.get_x()),
    yval = std::max(get_y(), other.get_y()),
    x2val = std::min(get_x() + get_width(),
		     other.get_x() + other.get_width()),
    y2val = std::min(get_y() + get_height(),
		     other.get_y() + other.get_height());

  if(xval <= x2val and yval <= y2val)
    return Rectangle(xval, yval, x2val - xval, y2val - yval);
  else
    return Rectangle();
}

Rectangle Rectangle::join(const Rectangle& other) const
{
  gj_assert(is_valid() and other.is_valid());

  double xval = std::min(get_x(), other.get_x()),
    yval = std::min(get_y(), other.get_y()),
    x2val = std::max(get_x() + get_width(),
		     other.get_x() + other.get_width()),
    y2val = std::max(get_y() + get_height(),
		     other.get_y() + other.get_height());

  return Rectangle(xval, yval, x2val - xval, y2val - yval);
}

bool Rectangle::is_above(const Rectangle& other) const
{
  gj_assert(is_valid() and other.is_valid());

  return get_y() + get_height() < other.get_y();
}

bool Rectangle::is_below(const Rectangle& other) const
{
  gj_assert(is_valid() and other.is_valid());

  return other.get_y() + other.get_height() < get_y();
}

bool Rectangle::is_valid() const
{
  return get_width() >= 0 && get_height() >= 0;
}

double Rectangle::get_area() const
{
  if(is_valid())
    return get_width() * get_height();
  return 0;
}
