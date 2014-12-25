#include "Background.hh"

#include <gdkmm/general.h>
#include <pangomm.h>

#include "Page.hh"
#include "util/Error.hh"

const double graphSize = 14.17;
const double rulingSize = 24;

const Color rulerColor(0x40a0ff);
const Color lineColor(0xff0080);
const Color backColor(0xffffff);
const Color noBackColor(0xaaaaaa);

Background::Background(Page& page_)
  : Glib::ObjectBase(typeid(Background)),
    background_type(SOLID),
    background_style(NONE),
    background_color(0xffffff),
    page(page_)
{

}

void Background::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{

  if(background_type == SOLID)
  {
    background_color.apply(cr);
    cr->paint();

    switch(background_style)
    {
    case Background::NONE:
      break;
    case Background::LINED:
      draw_background_lined(cr);
    case Background::RULED:
      draw_background_ruled(cr);
      break;
    case Background::GRAPH:
      draw_background_graph(cr);
      break;
    }
  }
  else if(background_type == IMAGE)
  {
    if(not(background_image))
    {
      draw_missing_background(cr);
      return;
    }

    double
      sx = page.get_width() / double(background_image->get_width()),
      sy = page.get_height() / double(background_image->get_height());

    cr->scale(sx, sy);

    Gdk::Cairo::set_source_pixbuf(cr, background_image);

    cr->paint();
  }
}

void Background::draw_missing_background(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  noBackColor.apply(cr);
  cr->paint();

  const double width_factor = 3/4.;

  Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);
  Pango::FontDescription font("Sans 48");
  font.set_weight(Pango::WEIGHT_SEMIBOLD);

  layout->set_font_description(font);
  layout->set_alignment(Pango::ALIGN_CENTER);
  layout->set_width(page.get_width() * width_factor * Pango::SCALE);
  layout->set_text("Missing background image");

  Color(0xffffff).apply(cr);

  cr->move_to(0, 0);
  //cr->move_to(page.get_width() / 2, page.get_height() / 2);

  int width, height;

  layout->get_size(width, height);

  width /= Pango::SCALE;
  height /= Pango::SCALE;

  cr->rel_move_to(page.get_width() * (1 - width_factor)/2.,
                  (page.get_height() - height) / 2);

  layout->show_in_cairo_context(cr);
}


void Background::draw_background_ruled(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);

  cr->set_line_width(0.5);

  for(double y = 80; y < page.get_height(); y += rulingSize)
  {
    cr->move_to(0, y);
    cr->line_to(page.get_width(), y);
  }

  cr->stroke();
}

void Background::draw_background_lined(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  lineColor.apply(cr);

  cr->set_line_width(0.5);
  cr->move_to(72, 0);
  cr->line_to(72, page.get_height());
  cr->stroke();
}

void Background::draw_background_graph(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  rulerColor.apply(cr);
  cr->set_line_width(0.5);

  for(double x = graphSize; x < page.get_width(); x += graphSize)
  {
    cr->move_to(x, 0);
    cr->line_to(x, page.get_height());
  }

  for(double y = graphSize; y < page.get_height(); y += graphSize)
  {
    cr->move_to(0, y);
    cr->line_to(page.get_width(), y);
  }

  cr->stroke();
}

void Background::set_color(Color c)
{
  background_color = c;
}

void Background::set_type(BackgroundType bg_type)
{
  background_type = bg_type;
}

void Background::set_style(BackgroundStyle bg_style)
{
  background_style = bg_style;
}

Glib::RefPtr<Gdk::Pixbuf> Background::get_image()
{
  return background_image;
}

void Background::set_image(Glib::RefPtr<Gdk::Pixbuf> image)
{
  background_image = image;
}
