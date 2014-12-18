#ifndef STROKE_HH
#define STROKE_HH

#include <list>
#include <memory>

#include <gdkmm/types.h>

#include "Element.hh"
#include "Point.hh"
#include "Pen.hh"
#include "Point.hh"
#include "Rectangle.hh"
#include "StrokeBase.hh"


typedef std::list<Point> PointList;

class Stroke;

typedef std::shared_ptr<Stroke> StrokeRef;


/**
 * @brief A Stroke of constant width
 */
class Stroke : public Element,
               public StrokeBase<Point>
{
private:
  Stroke(Pen pen_);

public:

  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
  virtual Rectangle bounding_rect() const override;

  virtual void move(Point& offset) override;
  virtual void scale(Point& src, double dx, double dy) override;

  /**
   * Creates a new Stroke
   */
  static StrokeRef create(Pen pen_);
};

#endif
