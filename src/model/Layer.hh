#ifndef LAYER_HH
#define LAYER_HH

#include <list>
#include <memory>

#include <cairomm/cairomm.h>

#include "Element.hh"

class Layer;
typedef std::shared_ptr<Layer> LayerRef;

class Layer
{
public:
  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;

  void add_element(ElementRef element);
  
  static LayerRef create();
  
private:
  Layer();
  std::list<ElementRef> elements;
};

#endif /* LAYER_HH */
