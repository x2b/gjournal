#ifndef RECTANGLE_HH
#define RECTANGLE_HH

#include <gdkmm/rectangle.h>

class Rectangle
{
public:
  Rectangle();
  bool isValid() const;
  
  double getX() const;
  double getY() const;
  
  double getWidth() const;
  double getHeight() const;
  
private:
  double x, y;
  double width, height;
  
};

#endif
