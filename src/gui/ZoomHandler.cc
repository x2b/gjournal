#include "ZoomHandler.hh"

#include "gui/JournalWidget.hh"
#include "gui/ZoomLevel.hh"

#include "util/Error.hh"
#include "util/Log.hh"

ZoomHandler::ZoomHandler(JournalWidget& parent_)
  : Glib::ObjectBase(typeid(ZoomHandler)),
    prop_zoom_level(*this, "zoom-level", 1.0),
    parent(parent_)
{

}

void ZoomHandler::set_zoom_level(double value)
{
  using namespace std::placeholders;

  // clamp the zoom level
  value = std::min(std::max(value, min_zoom),
                   max_zoom);

  //gj_assert(value >= min_zoom and value <= max_zoom);

  Gdk::Point pt = parent.get_scroll_handler().get_center_point();
  layout_pos = parent.get_layout().get_position(pt);
  Rectangle rect =
    parent.get_scroll_handler()
    .property_current_rectangle().get_value();

  fx = (pt.get_x() - rect.get_x()) / double(rect.get_width());
  fy = (pt.get_y() - rect.get_y()) / double(rect.get_height());

  LOG(DEBUG) << "ZoomHandler::set_zoom_level(" << value << ")";

  std::function<void(Gtk::Allocation&)> func
    = std::bind(&ZoomHandler::on_layout_size_allocated, this, _1);

  layout_con = parent.get_layout().signal_size_allocate().connect(func);

  prop_zoom_level = value;
}

double ZoomHandler::get_zoom_level() const
{
  return prop_zoom_level.get_value();
}

void ZoomHandler::zoom_in()
{
  set_zoom_level(std::min(max_zoom, get_zoom_level()*zoom_inc));
}

void ZoomHandler::zoom_out()
{
  set_zoom_level(std::max(min_zoom, get_zoom_level()/zoom_inc));
}

void ZoomHandler::zoom_fit_width()
{
  ///TODO: implement this
}

void ZoomHandler::zoom_fit_page()
{
  const ScrollHandler& handler =
    parent.get_scroll_handler();

  PageWidget* current_page_widget =
    handler.property_current_page().get_value();

  if(not(current_page_widget))
    return;

  Rectangle visible_rect =
    handler.property_current_rectangle().get_value();

  PageRef current_page =
    current_page_widget->get_page();

  double factor = std::min((visible_rect.get_width() - 2*page_margin) /
                           double(current_page->get_width()),
                           (visible_rect.get_height() - 2*page_margin) /
                           double(current_page->get_height()));

  set_zoom_level(factor);

  ///TODO: implement this
}

void ZoomHandler::on_layout_size_allocated(Gtk::Allocation&)
{
  TRACE;

  parent.get_scroll_handler().scroll_to_position(layout_pos, fx, fy);

  layout_con.disconnect();
}

