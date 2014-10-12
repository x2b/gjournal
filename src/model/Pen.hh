#ifndef PEN_HH
#define PEN_HH

#include <glibmm/object.h>
#include <glibmm/property.h>

#include <cairomm/cairomm.h>

#include "Color.hh"

class Pen : public Glib::Object
{
public:
  Pen();

  void apply(const Cairo::RefPtr<Cairo::Context>& cr) const;
  
  double getWidth();
  void setWidth(double width);
  
  Color& getColor();
  
private:
  Glib::Property<double> prop_width;
  Color color;
};

#endif
