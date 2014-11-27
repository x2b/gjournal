#include "ZoomHandler.hh"

#include "gui/JournalWidget.hh"

#include "util/Error.hh"
#include "util/Log.hh"

const float max_zoom = 2.0f;
const float min_zoom = 0.5f;
const float zoom_inc = 1.1f;

ZoomHandler::ZoomHandler(JournalWidget& parent_)
  : Glib::ObjectBase(typeid(ZoomHandler)),
    prop_zoom_level(*this, "zoom-level", 1.0f),
    parent(parent_)
{
  
}

void ZoomHandler::set_zoom_level(float value)
{
  gj_assert(value >= min_zoom and value <= max_zoom);
  
  Gdk::Point pt = parent.get_scroll_handler().get_center_point();
  LayoutPosition pos = parent.get_layout().get_position(pt);
  Gdk::Rectangle rect =
    parent.get_scroll_handler().get_current_rectangle();

  float fx = (pt.get_x() - rect.get_x()) / rect.get_width();
  float fy = (pt.get_y() - rect.get_y()) / rect.get_height();
    
  /* TODO: implement the zoom functionality
   *       such that changing the zoom does not change
   *       the position in the layout
   */
  
  LOG(DEBUG) << "ZoomHandler::set_zoom_level: " << value;
  
  prop_zoom_level = value;

  pt = parent.get_layout().get_point(pos);

  parent.get_scroll_handler().scroll_to(pt, fx, fy);
}

float ZoomHandler::get_zoom_level() const
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
  ///TODO: implement this
}


