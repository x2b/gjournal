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

  enum BackgroundType
  {
    NONE, LINED, RULED, GRAPH
  };

  double getWidth() const;
  double getHeight() const;
  int getNumber() const;
  
  void setNumber(int number);
  
  void setBackgroundType(BackgroundType _bg_type);

private:

  void drawBackground(const Cairo::RefPtr<Cairo::Context>& cr) const;

  void drawBackgroundRuled(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void drawBackgroundLined(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void drawBackgroundGraph(const Cairo::RefPtr<Cairo::Context>& cr) const;

  double width, height;
  int number;
  
  BackgroundType bg_type;

  std::list<std::shared_ptr<Layer>> layers;
};

typedef std::shared_ptr<Page> PageRef;

#endif
