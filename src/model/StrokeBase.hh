#ifndef STROKEBASE_HH
#define STROKEBASE_HH

#include <list>

#include "Pen.hh"

/**
 * @brief A container for points with an associated Pen.
 *
 * @tparam The point type
 */
template <typename P>
class StrokeBase
{
public:
  StrokeBase(Pen pen_)
    : pen(pen_)
  {
  }

  virtual ~StrokeBase()
  {
  }

  typedef std::list<P> Container;

  Container& get_points()
  {
    return points;
  }

  const Container& get_points() const
  {
    return points;
  }

  const Pen& get_pen() const
  {
    return pen;
  }

private:
  Container points;
  Pen pen;
};


#endif /* STROKEBASE_HH */
