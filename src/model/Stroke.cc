#include "Stroke.hh"

#include "util/Log.hh"

Stroke::Stroke(Pen pen_)
  : pen(pen_)
{
  
}

void Stroke::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  pen.apply(cr);

  if(points.empty())
    return;

  bool first = true;

  cr->set_line_join(Cairo::LINE_JOIN_ROUND);
  cr->set_line_cap(Cairo::LINE_CAP_ROUND);

  LOG(DEBUG) << "Drawing stroke...";
  
  for(const Gdk::Point& point : get_points())
  {
    if(first)
    {
      LOG(DEBUG) << "Moving to " << point.get_x()
		 << ", " << point.get_y();
      
      cr->move_to(point.get_x(), point.get_y());
      first = false;
      continue;
    }
    
    cr->line_to(point.get_x(), point.get_y());
    LOG(DEBUG) << "Drawing line to " << point.get_x()
	       << ", " << point.get_y();
  }

  cr->stroke();

}

Rectangle Stroke::bounding_rect() const
{
  return Rectangle();
}

void Stroke::move(Gdk::Point& offset)
{
  for(Gdk::Point& point : get_points())
  {
    point.set_x(point.get_x() + offset.get_x());
    point.set_y(point.get_y() + offset.get_y());
  }
}

void Stroke::scale(Gdk::Point& src, double dx, double dy)
{
  double ox = src.get_x(),
         oy = src.get_y();

  for(Gdk::Point& point : get_points())
  {
    double x = point.get_x(),
           y = point.get_y();

    point.set_x(x + dx * (point.get_x() - ox));
    point.set_y(y + dy * (point.get_y() - oy));
  }
}

PointList& Stroke::get_points()
{
  return points;
}

const PointList& Stroke::get_points() const
{
  return points;
}

StrokeRef Stroke::create(Pen pen_)
{
  return StrokeRef(new Stroke(pen_));
}
