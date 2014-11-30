#include "PressureStroke.hh"

PressureStroke::PressureStroke(Pen pen_)
  : StrokeBase(pen_)
{
}

void PressureStroke::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  get_pen().apply(cr);

  if(get_points().empty())
    return;

  bool first = true;
  Point last_point(0, 0);

  for(const PressurePoint& point : get_points())
  {
    if(first)
    {
      first = false;
    }
    else
    {
      cr->move_to(last_point.get_x(), last_point.get_y());
      cr->set_line_width(point.get_z());
      cr->line_to(point.get_x(), point.get_y());
      cr->stroke();
    }

    last_point = point;
  }
}

Rectangle PressureStroke::bounding_rect() const
{
  return Rectangle();
}

void PressureStroke::move(Point& offset)
{
  ///TODO: implement this
}

void PressureStroke::scale(Point& src, double dx, double dy)
{
  ///TODO: implement this
}

PressureStrokeRef PressureStroke::create(Pen pen_)
{
  return PressureStrokeRef(new PressureStroke(pen_));
}
