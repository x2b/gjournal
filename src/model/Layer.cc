#include "Layer.hh"

void Layer::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  for(auto element : elements)
  {
    element->draw(cr);
  }
}
