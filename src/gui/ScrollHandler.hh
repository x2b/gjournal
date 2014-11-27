#ifndef SCROLLHANDLER_HH
#define SCROLLHANDLER_HH

#include <gdkmm/types.h>
#include <gdkmm/rectangle.h>

class JournalWidget;
class PageLayout;

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
   * Scrolls such that the given point
   * is at a fraction of fx / fy
   * of the dimensions of the
   * visible rectangle
   */
  void scroll_to(Gdk::Point point,
                 float fx,
                 float fy);

  /**
   * Returns the point in the middle of the visible rectangle
   */		 
  Gdk::Point get_center_point() const;
		 
private:
  JournalWidget& parent;
  PageLayout& layout;
};

#endif /* SCROLLHANDLER_HH */
