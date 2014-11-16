#ifndef STROKE_HH
#define STROKE_HH

#include <list>

#include <gdkmm/types.h>

#include "Element.hh"
#include "Pen.hh"
#include "Rectangle.hh"

typedef std::list<Gdk::Point> PointList;

class Stroke : public Element
{
public:

  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
  virtual Rectangle boundingRect() const override;

  virtual void move(Gdk::Point& offset) override;
  virtual void scale(Gdk::Point& src, double dx, double dy) override;

  PointList& getPoints();
  const PointList& getPoints() const;

private:
  Pen pen;
  PointList points;
};

#endif
