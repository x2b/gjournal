#ifndef ZOOMHANDLER_HH
#define ZOOMHANDLER_HH

#include <glibmm/object.h>
#include <glibmm/property.h>
#include <gtkmm/widget.h>

#include "gui/PageLayout.hh"

class JournalWidget;

/**
 * @brief The ZoomHandler stores the current zoom level
 */
class ZoomHandler : public Glib::Object
{
public:
  ZoomHandler(JournalWidget& parent_);

  Glib::PropertyProxy_ReadOnly<double> property_zoom_level() const
  {
    return Glib::PropertyProxy_ReadOnly<double>(this, "zoom-level");
  }

  double get_zoom_level() const;

  void set_zoom_level(double value);

  void zoom_in();
  void zoom_out();

  void zoom_fit_width();
  void zoom_fit_page();

private:
  void on_layout_size_allocated(Gtk::Allocation& alloc);

  Glib::Property<double> prop_zoom_level;
  JournalWidget& parent;

  sigc::connection layout_con;

  LayoutPosition layout_pos;
  double fx, fy;
};

#endif

