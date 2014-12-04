#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include <gdkmm/rectangle.h>

class Rectangle
{
public:
  Rectangle();
  Rectangle(double x_, double y_,
	    double width_, double height_);
  Rectangle(const Gdk::Rectangle& rect);
  bool is_valid() const;

  double get_x() const;
  double get_y() const;

  double get_width() const;
  double get_height() const;

  bool intersects(const Rectangle& other) const;
  bool is_above(const Rectangle& other) const;
  bool is_below(const Rectangle& other) const;

  Rectangle intersect(const Rectangle& other) const;
  Rectangle join(const Rectangle& other) const;

  double get_area() const;

private:
  double x, y;
  double width, height;

};

#endif
