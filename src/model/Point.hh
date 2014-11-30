#ifndef POINT_HH
#define POINT_HH

#include <iostream>

class Point
{
public:
  Point(double x_, double y_);

  void set_x(double x_);
  void set_y(double y_);

  double get_x() const;
  double get_y() const;

private:
  double x, y;

};


std::ostream& operator<<(std::ostream& stream,
			 const Point& point);

#endif /* POINT_HH */
