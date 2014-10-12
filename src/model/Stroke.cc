#include "Stroke.hh"


void Stroke::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  pen.apply(cr);
  
  if(points.empty())
    return;
  
  bool first = true;
  
  for(const Gdk::Point& point : getPoints())
  {
    if(first)
    {
      cr->move_to(point.get_x(), point.get_y());
      first = false;
    }
    else
    {
      cr->line_to(point.get_x(), point.get_y());
    }
  }
  
}

Rectangle Stroke::boundingRect() const
{
  return Rectangle();
}

void Stroke::move(Gdk::Point& offset)
{
  for(Gdk::Point& point : getPoints())
  {
    point.set_x(point.get_x() + offset.get_x());
    point.set_y(point.get_y() + offset.get_y());
  }
}

void Stroke::scale(Gdk::Point& src, double dx, double dy)
{
  double ox = src.get_x(),
         oy = src.get_y();
  
  for(Gdk::Point& point : getPoints())
  {
    double x = point.get_x(),
           y = point.get_y();
    
    point.set_x(x + dx * (point.get_x() - ox));
    point.set_y(y + dy * (point.get_y() - oy));
  }
}

PointList& Stroke::getPoints()
{
  return points;
}

const PointList& Stroke::getPoints() const
{
  return points;
}
