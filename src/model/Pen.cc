#include "Pen.hh"

#include "util/Error.hh"

Pen::Pen()
  : width(1)
{
}

double Pen::get_width() const
{
  return width;
}

void Pen::set_width(double width_)
{
  gj_assert(width_ > 0);
  
  width = width_;
}

Color Pen::get_color() const
{
  return color;
}

void Pen::set_color(Color col)
{
  color = col;
}

void Pen::apply(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  color.apply(cr);
  cr->set_line_width(width);
}
