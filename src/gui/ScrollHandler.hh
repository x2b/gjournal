#ifndef SCROLLHANDLER_HH
#define SCROLLHANDLER_HH

#include <gdkmm/types.h>
#include <gdkmm/rectangle.h>

#include "gui/PageLayout.hh"

class JournalWidget;

class ScrollHandler
{
public:
  ScrollHandler(JournalWidget& parent_);

  /**
   * Returns the rectangle of the underlying PageLayout
   * which is currently visible on the screen
   */
  Gdk::Rectangle get_current_rectangle() const;

  /**
   * Scrolls such that the LayoutPosition
   * is at a fraction of fx / fy
   * of the dimensions of the
   * visible rectangle
   */
  void scroll_to(LayoutPosition pos,
                 float fx,
                 float fy);

  /**
   * Returns the point in the middle of the visible rectangle
   */
  Gdk::Point get_center_point() const;

private:
  JournalWidget& parent;

  Glib::RefPtr<Gtk::Adjustment> hadj, vadj;
};

#endif /* SCROLLHANDLER_HH */
