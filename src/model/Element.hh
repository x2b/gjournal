#ifndef ELEMENT_HH
#define ELEMENT_HH

#include <memory>

#include <gdkmm/types.h>
#include <gdkmm/rectangle.h>

#include <cairomm/cairomm.h>

#include "Rectangle.hh"

class Element
{
public:
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const = 0;
  virtual Rectangle bounding_rect() const = 0;

  virtual void move(Gdk::Point& offset) = 0;
  virtual void scale(Gdk::Point& src, double dx, double dy) = 0;

};

typedef std::shared_ptr<Element> ElementRef;

#endif
