#ifndef PAGE_HH
#define PAGE_HH

#include <list>
#include <memory>

#include <glibmm/object.h>
#include <glibmm/property.h>

#include <cairomm/cairomm.h>

#include "Background.hh"
#include "Color.hh"
#include "Layer.hh"

class Page;

typedef std::shared_ptr<Page> PageRef;

/**
 * @brief A Document consists of a list of Page%s
 */
class Page : public Glib::Object
{
public:

  virtual ~Page();

  template<typename... Args>
  static PageRef create(Args&&... args)
  {
    Page* p = new Page(std::forward<Args>(args)...);
    return PageRef(p);
  }

  /**
   * Draws the Page using the provided Cario::Context.
   * The method will fill the Rectangle with the corners
   * 0,0 and dimensions Page::get_width() by Page::get_height()
   */
  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;


  /**
   * Adds a new Layer to this Page
   */
  void add_layer(LayerRef layer);

  /**
   * Returns the width of this Page in pixels
   */
  double get_width() const;

  /**
   * Returns the height of this Page in pixels
   */
  double get_height() const;

  /**
   * Returns the number of this Page
   */
  int get_number() const;

  /**
   * Sets this Page%'s number
   */
  void set_number(int number);

  Background& get_background();
  const Background& get_background() const;

private:
  Page(double width, double height, int number = -1);

  double width, height;
  int number;

  std::list<LayerRef> layers;
  Background background;
};

#endif
