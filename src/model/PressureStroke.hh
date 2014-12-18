#ifndef PRESSURESTROKE_HH
#define PRESSURESTROKE_HH

#include "Element.hh"
#include "PressurePoint.hh"
#include "StrokeBase.hh"


class PressureStroke;

typedef std::shared_ptr<PressureStroke> PressureStrokeRef;


/**
 * @brief A Stroke of variable width
 */
class PressureStroke : public Element,
                       public StrokeBase<PressurePoint>
{
private:
  PressureStroke(Pen pen_);

public:
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
  virtual Rectangle bounding_rect() const override;

  virtual void move(Point& offset) override;
  virtual void scale(Point& src, double dx, double dy) override;

  /**
   * Creates a new PressureStroke.
   */
  static PressureStrokeRef create(Pen pen_);
};

#endif /* PRESSURESTROKE_HH */
