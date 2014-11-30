#include "Text.hh"

#include <pangomm/layout.h>

Text::Text(const Glib::ustring& text_,
           const Glib::ustring& font_desc,
           const double& font_size,
           const Point& point_)
  : text(text_), point(point_), color(0)
{
  font.set_family(font_desc);
  font.set_size(font_size * Pango::SCALE);
}

void Text::set_color(Color c)
{
  color = c;
}

void Text::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  cr->move_to(point.get_x(), point.get_y());

  color.apply(cr);

  Glib::RefPtr<Pango::Layout> layout =
    Pango::Layout::create(cr);

  layout->set_text(text);
  layout->set_font_description(font);

  layout->show_in_cairo_context(cr);
}

Rectangle Text::bounding_rect() const
{
  return Rectangle();
}

void Text::move(Point& offset)
{
  point = Point(point.get_x() + offset.get_x(),
                     point.get_y() + offset.get_y());
}

void Text::scale(Point& src, double dx, double dy)
{
  ///TODO: implement
}


TextRef Text::create(const Glib::ustring& text_,
                     const Glib::ustring& font_desc,
                     const double& font_size,
                     const Point& point_)
{
  return TextRef(new Text(text_, font_desc,
                          font_size, point_));
}

Text::~Text()
{

}
