#include "JournalWidget.hh"

#include <giomm/file.h>

#include "gui/PageWidget.hh"
#include "util/Log.hh"

JournalWidget::JournalWidget(DocumentRef doc_)
  : doc(doc_),
    viewport(nullptr),
    scroll_handler(*this),
    zoom_handler(*this)
{
  viewport = Gtk::manage(new Gtk::Viewport(get_hadjustment(),
                                           get_vadjustment()));

  viewport->set_hadjustment(get_hadjustment());
  viewport->set_vadjustment(get_vadjustment());

  viewport->add(page_layout);
  add(*viewport);

  pages.reserve(doc->count_pages());

  for(PageRef& page : doc->get_pages())
  {
    PageWidget* widget = Gtk::manage(new PageWidget(page, this));
    page_layout.add(*widget);
    pages.push_back(widget);
  }

  page_layout.set_margin_top(30);
  page_layout.set_margin_bottom(30);
}

JournalWidget::~JournalWidget()
{
  TRACE;
  //delete viewport;
}

Glib::ustring JournalWidget::get_title() const
{
  Glib::ustring uri = doc->get_uri();

  if(uri.empty())
  {
    return("untitled");
  }
  else
  {
    auto file = Gio::File::create_for_uri(uri);
    return file->get_basename();
  }
}

PageLayout& JournalWidget::get_layout()
{
  return page_layout;
}

Gdk::Rectangle JournalWidget::get_rectangle(PageWidget& widget)
{
  Gdk::Rectangle rect;

  rect.set_width(widget.get_allocated_width());
  rect.set_height(widget.get_allocated_height());

  int x = 0, y = 0;

  widget.translate_coordinates(get_layout(), 0, 0, x, y);

  rect.set_x(x);
  rect.set_y(y);

  return rect;
}

ScrollHandler& JournalWidget::get_scroll_handler()
{
  return scroll_handler;
}


ZoomHandler& JournalWidget::get_zoom_handler()
{
  return zoom_handler;
}

DocumentRef JournalWidget::get_document()
{
  return doc;
}

bool JournalWidget::on_scroll_event(GdkEventScroll* event)
{
  if((event->state & GDK_CONTROL_MASK))
  {
    LOG(DEBUG) << "JournalWidget::on_scroll_event";

    if(event->direction == GDK_SCROLL_UP)
    {
      zoom_handler.zoom_in();
    }
    else if(event->direction == GDK_SCROLL_DOWN)
    {
      zoom_handler.zoom_out();
    }
    else
    {
      LOG(ERROR) << "Invalid zoom direction";
    }

    return true;
  }

  return Gtk::ScrolledWindow::on_scroll_event(event);
}

bool JournalWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  bool v = Gtk::ScrolledWindow::on_draw(cr);

#if 0
  int xmin, xmax, ymin, ymax;

  Gdk::Rectangle rect = viewport->get_allocation();

  viewport->translate_coordinates(*this,
                                  rect.get_x(),
                                  rect.get_y(),
                                  xmin, ymin);

  viewport->translate_coordinates(*this,
                                  rect.get_x() + rect.get_width(),
                                  rect.get_y() + rect.get_height(),
                                  xmax, ymax);

  rect = Gdk::Rectangle(xmin, ymin, xmax - xmin, ymax - ymin);

  cr->set_source_rgb(1., 0, 0);

  /*
    cr->rectangle(rect.get_x(), rect.get_y(),
    rect.get_x() + rect.get_width(),
    rect.get_y() + rect.get_height());

    cr->stroke();
  */


  Glib::RefPtr<Pango::Layout> layout = Pango::Layout::create(cr);
  Pango::FontDescription font("Sans 14");

  layout->set_font_description(font);
  layout->set_alignment(Pango::ALIGN_RIGHT);
  layout->set_justify();
  layout->set_width(rect.get_width() * Pango::SCALE);

  std::ostringstream str;

  get_debug_msg(str);

  layout->set_text(str.str());

  cr->move_to(0, 0);

  int width, height;

  layout->get_size(width, height);

  width /= Pango::SCALE;
  height /= Pango::SCALE;

  cr->rel_move_to(-5, height);

  layout->show_in_cairo_context(cr);

#endif

  return v;
}

void JournalWidget::get_debug_msg(std::ostringstream& str)
{
  Rectangle rect =
    get_scroll_handler().property_current_rectangle().get_value();

  Gdk::Point point = get_scroll_handler().get_center_point();

  LayoutPosition pos = get_layout().get_position(point);

  /*
    auto hadj = viewport->get_hadjustment();
    auto vadj = viewport->get_vadjustment();
  */

  str << "Visible rectangle: \n"
      << rect.get_x() << ", " << rect.get_y()
      << ", w = " << rect.get_width()
      << ", h = " << rect.get_height() << "\n"
      << "Center point: \n"
      << point.get_x() << ", " << point.get_y() << "\n"
      << "Layout position: \n"
      << pos.space_above << ", " << pos.space_left << "\n";
}
