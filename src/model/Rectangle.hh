#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include <gdkmm/rectangle.h>

/**
 * @brief An axis-parallel Rectangle
 */
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

  /**
   * Returns this Rectangle%'s width.
   */
  double get_width() const;
  /**
   * Returns this Rectangle%'s height.
   */
  double get_height() const;

  /**
   * Returns whether this Rectangle intersects the other.
   */
  bool intersects(const Rectangle& other) const;

  /**
   * Returns whether this Rectangle is stricly above the other.
   */
  bool is_above(const Rectangle& other) const;

  /**
   * Returns whether this Rectangle is stricly below the other.
   */
  bool is_below(const Rectangle& other) const;

  /**
   * Returns the intersection of this Rectangle with the other.
   */
  Rectangle intersect(const Rectangle& other) const;

  /**
   * Returns the smallest Rectangle containing the union of this
   * Rectangle and the other.
   */
  Rectangle join(const Rectangle& other) const;

  /**
   * Returns the area of this Rectangle.
   */
  double get_area() const;

private:
  double x, y;
  double width, height;

};

#endif
