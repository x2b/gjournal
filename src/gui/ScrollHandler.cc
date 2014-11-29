#include "ScrollHandler.hh"

#include "JournalWidget.hh"
#include "PageLayout.hh"

#include "util/Log.hh"

ScrollHandler::ScrollHandler(JournalWidget& parent_)
  : parent(parent_),
    hadj(parent.get_hadjustment()),
    vadj(parent.get_vadjustment())
{

}

Gdk::Rectangle ScrollHandler::get_current_rectangle() const
{
  return Gdk::Rectangle(hadj->get_value(),
                        vadj->get_value(),
                        hadj->get_page_size(),
                        vadj->get_page_size());
}

void ScrollHandler::scroll_to(LayoutPosition pos,
                              float fx,
                              float fy)
{
  const double dx = hadj->get_page_size();
  const double dy = vadj->get_page_size();

  Gdk::Point point(parent.get_layout().get_point(pos));

  const double x = point.get_x() - fx*dx,
    y = point.get_y() - fy*dy;

  LOG(DEBUG) << "Scrolling to position "
	     << x << ", " << y;

  hadj->set_value(x);
  vadj->set_value(y);
}

Gdk::Point ScrollHandler::get_center_point() const
{
  return Gdk::Point(hadj->get_value() + hadj->get_page_size() / 2,
		    vadj->get_value() + vadj->get_page_size() / 2);
}
