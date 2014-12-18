#ifndef ELEMENT_HH
#define ELEMENT_HH

#include <memory>

#include <gdkmm/types.h>
#include <gdkmm/rectangle.h>

#include <cairomm/cairomm.h>

#include "Rectangle.hh"
#include "Point.hh"

/**
 * @brief Element%s populate the Layer%s of a Page
 */
class Element
{
public:

  /**
   * Draws this Element using the provided Cairo::Context.
   */
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const = 0;

  /**
   * Returns the bounding Rectangle of this Element.
   */
  virtual Rectangle bounding_rect() const = 0;

  /**
   * Moves this Element by the specified offset
   */
  virtual void move(Point& offset) = 0;

  /**
   * Scales this Element by factors dx, dy around the given
   * src
   */
  virtual void scale(Point& src, double dx, double dy) = 0;

};

typedef std::shared_ptr<Element> ElementRef;

#endif
