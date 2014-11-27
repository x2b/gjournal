#ifndef ZOOMHANDLER_HH
#define ZOOMHANDLER_HH

#include <glibmm/object.h>
#include <glibmm/property.h>

class JournalWidget;

/**
 * @brief The ZoomHandler stores the current zoom level
 */
class ZoomHandler : public Glib::Object
{
public:
  ZoomHandler(JournalWidget& parent_);

  Glib::PropertyProxy_ReadOnly<float> property_zoom_level() const
  {
    return Glib::PropertyProxy_ReadOnly<float>(this, "zoom-level");
  }
  
  float get_zoom_level() const;
  
  void set_zoom_level(float value);

  void zoom_in();
  void zoom_out();
  
  void zoom_fit_width();
  void zoom_fit_page();
  
private:
  Glib::Property<float> prop_zoom_level;

  JournalWidget& parent;
};

#endif
