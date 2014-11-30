#include "Layer.hh"

Layer::Layer()
{
}

void Layer::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  for(auto element : elements)
  {
    if(not(element))
      continue;

    cr->save();
    element->draw(cr);
    cr->restore();
  }
}

void Layer::add_element(ElementRef element)
{
  elements.push_back(element);
}

LayerRef Layer::create()
{
  return LayerRef(new Layer());
}
