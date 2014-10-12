#include "Pen.hh"

Pen::Pen()
  : Glib::ObjectBase(typeid(Pen)),
    prop_width(*this, "width", 1)
{
}

Color& Pen::getColor()
{
  return color;
}

void Pen::apply(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  color.apply(cr);
  cr->set_line_width(prop_width);
}
