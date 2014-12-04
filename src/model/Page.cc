#include "Page.hh"

#include "util/Log.hh"

const double graphSize = 14.17;
const double rulingSize = 24;

Color rulerColor(0x40a0ff);
Color lineColor(0xff0080);
Color backColor(0xffffff);

Page::Page(double width_, double height_,
	   int number_)
  : Glib::ObjectBase(typeid(Page)),
    width(width_), height(height_), number(number_),
    background_color(backColor),
    bg_type(BackgroundType::NONE)
{
}

Page::~Page()
{
  TRACE;
}

void Page::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  draw_background(cr);

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

void Page::set_background_color(Color c_)
{
  background_color = c_;
}

void Page::set_background_type(BackgroundType bg_type_)
{
  bg_type = bg_type_;
}

void Page::draw_background(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  background_color.apply(cr);
  cr->paint();

  switch(bg_type)
  {
  case BackgroundType::NONE:
    break;
  case BackgroundType::LINED:
    draw_background_lined(cr);
  case BackgroundType::RULED:
    draw_background_ruled(cr);
    break;
  case BackgroundType::GRAPH:
    draw_background_graph(cr);
    break;
  }
}

void Page::draw_background_ruled(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);

  cr->set_line_width(0.5);

  for(double y = 80; y < get_height(); y += rulingSize)
  {
    cr->move_to(0, y);
    cr->line_to(get_width(), y);
  }

  cr->stroke();
}

void Page::draw_background_lined(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  lineColor.apply(cr);

  cr->set_line_width(0.5);
  cr->move_to(72, 0);
  cr->line_to(72, get_height());
  cr->stroke();
}

void Page::draw_background_graph(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);
  cr->set_line_width(0.5);

  for(double x = graphSize; x < get_width(); x += graphSize)
  {
    cr->move_to(x, 0);
    cr->line_to(x, get_height());
  }

  for(double y = graphSize; y < get_height(); y += graphSize)
  {
    cr->move_to(0, y);
    cr->line_to(get_width(), y);
  }

  cr->stroke();
}
