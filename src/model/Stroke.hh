#ifndef STROKE_HH
#define STROKE_HH

#include <list>
#include <memory>

#include <gdkmm/types.h>

#include "Element.hh"
#include "Pen.hh"
#include "Rectangle.hh"

typedef std::list<Gdk::Point> PointList;

class Stroke;

typedef std::shared_ptr<Stroke> StrokeRef;

class Stroke : public Element
{
private:
  Stroke(Pen pen_);
  
public:

  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
  virtual Rectangle bounding_rect() const override;

  virtual void move(Gdk::Point& offset) override;
  virtual void scale(Gdk::Point& src, double dx, double dy) override;

  PointList& get_points();
  const PointList& get_points() const;

  static StrokeRef create(Pen pen_);

private:
  Pen pen;
  PointList points;
};

#endif
