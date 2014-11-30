#include "Point.hh"

Point::Point(double x_, double y_)
  : x(x_), y(y_)
{
}

void Point::set_x(double x_)
{
  x = x_;
}

void Point::set_y(double y_)
{
  y = y_;
}

double Point::get_x() const
{
  return x;
}

double Point::get_y() const
{
  return y;
}

std::ostream& operator<<(std::ostream& stream,
                         const Point& point)
{
  stream << "Point(" << point.get_x()
         << ", " << point.get_y() << ")";

  return stream;
}
