#ifndef LAYER_HH
#define LAYER_HH

#include <list>
#include <memory>

#include <cairomm/cairomm.h>

#include "Element.hh"

class Layer
{
public:
  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;

private:

  std::list<std::shared_ptr<Element>> elements;
};

#endif
