#include "Page.hh"

#include "Color.hh"

const double graphSize = 14.17;
const double rulingSize = 24;

Color rulerColor(0x40a0ff);
Color lineColor(0xff0080);
Color backColor(0xffffff);

Page::Page(double width, double height, int number)
  : Glib::ObjectBase(typeid(Page)),
    width(width), height(height), number(number),
    bg_type(NONE)
{
}

void Page::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  drawBackground(cr);

  for(auto layer : layers)
  {
    layer->draw(cr);
  }
}

double Page::getWidth() const
{
  return width;
}

double Page::getHeight() const
{
  return height;
}

int Page::getNumber() const
{
  return number;
}

void Page::setNumber(int _number)
{
  number = _number;
}

void Page::setBackgroundType(BackgroundType _bg_type)
{
  bg_type = _bg_type;
}

void Page::drawBackground(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  backColor.apply(cr);
  cr->paint();
  
  switch(bg_type)
  {
    case NONE:
      break;
    case LINED:
      drawBackgroundLined(cr);
    case RULED:
      drawBackgroundRuled(cr);
      break;
    case GRAPH:
      drawBackgroundGraph(cr);
      break;
  }
}

void Page::drawBackgroundRuled(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);

  cr->set_line_width(0.5);

  for(double y = 80; y < getHeight(); y += rulingSize)
  {
    cr->move_to(0, y);
    cr->line_to(getWidth(), y);
  }
  
  cr->stroke();
}

void Page::drawBackgroundLined(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  lineColor.apply(cr);
  
  cr->set_line_width(0.5);
  cr->move_to(72, 0);
  cr->line_to(72, getHeight());
  cr->stroke();
}

void Page::drawBackgroundGraph(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);
  cr->set_line_width(0.5);

  for(double x = graphSize; x < getWidth(); x += graphSize)
  {
    cr->move_to(x, 0);
    cr->line_to(x, getHeight());
  }
  
  for(double y = graphSize; y < getHeight(); y += graphSize)
  {
    cr->move_to(0, y);
    cr->line_to(getWidth(), y);
  }
  
  cr->stroke();
}
