#ifndef SCROLLHANDLER_HH
#define SCROLLHANDLER_HH

#include <glibmm/object.h>
#include <gdkmm/types.h>
#include <gdkmm/rectangle.h>

#include "gui/PageLayout.hh"
#include "gui/PageWidget.hh"
#include "model/Rectangle.hh"

class JournalWidget;

class ScrollHandler : public Glib::Object
{
public:
  ScrollHandler(JournalWidget& parent_);

  /**
   * Scrolls such that the LayoutPosition
   * is at a fraction of fx / fy
   * of the dimensions of the
   * visible rectangle
   */
  void scroll_to_position(LayoutPosition pos,
                          float fx = 0.5,
                          float fy = 0.5);

  /**
   * Scrolls such that the given PageRef
   * is at a fraction of fx / fy
   * of the dimensions of the
   * visible rectangle
   */
  void scroll_to_page(PageWidget* page,
                      float fx = 0,
                      float fy = 0,
                      bool leave_space = false);

  /**
   * Returns the point in the middle of the visible rectangle
   */
  Gdk::Point get_center_point() const;

  Glib::PropertyProxy<Rectangle> property_current_rectangle();
  Glib::PropertyProxy_ReadOnly<Rectangle> property_current_rectangle() const;

  Glib::PropertyProxy<PageWidget*> property_current_page();
  Glib::PropertyProxy_ReadOnly<PageWidget*> property_current_page() const;

private:
  void on_adjustment_changed();

  /**
   * Returns the rectangle of the underlying PageLayout
   * which is currently visible on the screen
   */
  Rectangle compute_current_rectangle() const;

  PageWidget* compute_current_page() const;

  JournalWidget& parent;

  Glib::Property<Rectangle> prop_current_rectangle;
  Glib::Property<PageWidget*> prop_current_page;
  Glib::RefPtr<Gtk::Adjustment> hadj, vadj;
};

#endif /* SCROLLHANDLER_HH */
