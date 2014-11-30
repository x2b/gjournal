#ifndef PEN_HH
#define PEN_HH

#include <glibmm/object.h>
#include <glibmm/property.h>

#include <cairomm/cairomm.h>

#include "Color.hh"

class Pen
{
public:
  Pen();

  void apply(const Cairo::RefPtr<Cairo::Context>& cr) const;

  double get_width() const;
  void set_width(double width);

  Color get_color() const;
  void set_color(Color col);

private:
  double width;
  Color color;
};

#endif
