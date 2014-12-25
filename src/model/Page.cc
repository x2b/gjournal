#include "Page.hh"

#include "util/Log.hh"

Page::Page(double width_, double height_,
	   int number_)
  : Glib::ObjectBase(typeid(Page)),
    width(width_), height(height_), number(number_),
    background(*this)
{
}

Page::~Page()
{
  TRACE;
}

void Page::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  background.draw(cr);

  for(auto layer : layers)
  {
    layer->draw(cr);
  }
}

void Page::add_layer(LayerRef layer)
{
  layers.push_back(layer);
}

double Page::get_width() const
{
  return width;
}

double Page::get_height() const
{
  return height;
}

int Page::get_number() const
{
  return number;
}

void Page::set_number(int number_)
{
  number = number_;
}

Background& Page::get_background()
{
  return background;
}

const Background& Page::get_background() const
{
  return background;
}
