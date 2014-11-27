#ifndef PAGE_HH
#define PAGE_HH

#include <list>
#include <memory>

#include <glibmm/object.h>
#include <glibmm/property.h>

#include <cairomm/cairomm.h>

#include "Layer.hh"

class Page : public Glib::Object
{
public:
  Page(double width, double height, int number = -1);
	
  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;

  enum class BackgroundType
  {
    NONE, LINED, RULED, GRAPH
  };

  double get_width() const;
  double get_height() const;
  int get_number() const;

  void set_number(int number);

  void set_background_type(BackgroundType bg_type_);

private:

  void draw_background(const Cairo::RefPtr<Cairo::Context>& cr) const;

  void draw_background_ruled(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void draw_background_lined(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void draw_background_graph(const Cairo::RefPtr<Cairo::Context>& cr) const;

  double width, height;
  int number;

  BackgroundType bg_type;

  std::list<std::shared_ptr<Layer>> layers;
};

typedef std::shared_ptr<Page> PageRef;

#endif
