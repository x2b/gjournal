#include "ScrollHandler.hh"

#include "JournalWidget.hh"
#include "PageLayout.hh"

ScrollHandler::ScrollHandler(JournalWidget& parent_)
  : parent(parent_),
    layout(parent.get_layout())
{

}

Gdk::Rectangle ScrollHandler::get_current_rectangle() const
{
  auto hadj = layout.get_hadjustment();
  auto vadj = layout.get_vadjustment();

  return Gdk::Rectangle(hadj->get_value(),
                        vadj->get_value(),
                        hadj->get_page_increment(),
                        vadj->get_page_increment());
}

void ScrollHandler::scroll_to(Gdk::Point point,
                              float fx,
                              float fy)
{
  auto hadj = layout.get_hadjustment();
  auto vadj = layout.get_vadjustment();

  double dx = vadj->get_page_increment();
  double dy = hadj->get_page_increment();

  vadj->set_value(point.get_x() - fx*dx);
  hadj->set_value(point.get_y() - fy*dy);
  
}

Gdk::Point ScrollHandler::get_center_point() const
{
  auto hadj = layout.get_hadjustment();
  auto vadj = layout.get_vadjustment();

  return Gdk::Point(vadj->get_value() + vadj->get_page_increment() / 2,
		    hadj->get_value() + hadj->get_page_increment() / 2);
}
