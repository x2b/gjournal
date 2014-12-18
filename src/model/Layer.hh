#ifndef LAYER_HH
#define LAYER_HH

#include <list>
#include <memory>

#include <cairomm/cairomm.h>

#include "Element.hh"

class Layer;
typedef std::shared_ptr<Layer> LayerRef;

/**
 * @brief A Page consists of Layer%s
 *
 * The layers are drawn according to their order
 * in the Page
 */
class Layer
{
public:
  /**
   * Draws the Element%s contained in this Layer
   * using the provided Cairo::Context
   */
  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;

  /**
   * Adds an Element to this Layer.
   */
  void add_element(ElementRef element);

  /**
   * Creates a new (empty) Layer.
   */
  static LayerRef create();

private:
  Layer();
  std::list<ElementRef> elements;
};

#endif /* LAYER_HH */
