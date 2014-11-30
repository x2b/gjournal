#include "Stroke.hh"

#include "util/Log.hh"

Stroke::Stroke(Pen pen_)
  : StrokeBase(pen_)
{

}

void Stroke::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  get_pen().apply(cr);

  if(get_points().empty())
    return;

  bool first = true;

  for(const Point& point : get_points())
  {
    if(first)
    {
      cr->move_to(point.get_x(), point.get_y());
      first = false;
      continue;
    }

    cr->line_to(point.get_x(), point.get_y());
  }

  cr->stroke();
}

Rectangle Stroke::bounding_rect() const
{
  return Rectangle();
}

void Stroke::move(Point& offset)
{
  for(Point& point : get_points())
  {
    point.set_x(point.get_x() + offset.get_x());
    point.set_y(point.get_y() + offset.get_y());
  }
}

void Stroke::scale(Point& src, double dx, double dy)
{
  double ox = src.get_x(),
         oy = src.get_y();

  for(Point& point : get_points())
  {
    double x = point.get_x(),
           y = point.get_y();

    point.set_x(x + dx * (point.get_x() - ox));
    point.set_y(y + dy * (point.get_y() - oy));
  }
}

StrokeRef Stroke::create(Pen pen_)
{
  return StrokeRef(new Stroke(pen_));
}
