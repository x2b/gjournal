#include "ScrollHandler.hh"

#include "gui/JournalWidget.hh"
#include "gui/PageLayout.hh"
#include "gui/PageWidget.hh"

#include "util/Error.hh"
#include "util/Log.hh"

ScrollHandler::ScrollHandler(JournalWidget& parent_)
  : Glib::ObjectBase(typeid(ScrollHandler)),
    parent(parent_),
    prop_current_rectangle(*this, "current-rectangle", Rectangle()),
    prop_current_page(*this, "current-page", nullptr),
    hadj(parent.get_hadjustment()),
    vadj(parent.get_vadjustment())
{
  auto func = std::bind(&ScrollHandler::on_adjustment_changed, this);

  for(auto& adj : std::vector<decltype(hadj)>{hadj, vadj})
  {
    adj->signal_changed().connect(func);
    adj->signal_value_changed().connect(func);
  }

  auto& pages = parent.get_page_widgets();

  if(not(pages.empty()))
    prop_current_page.set_value(*pages.begin());
}

Rectangle ScrollHandler::compute_current_rectangle() const
{
  return Rectangle(hadj->get_value(),
                   vadj->get_value(),
                   hadj->get_page_size(),
                   vadj->get_page_size());
}

void ScrollHandler::scroll_to_position(LayoutPosition pos,
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

void ScrollHandler::scroll_to_page(PageWidget* page,
                                   float fx,
                                   float fy,
                                   bool leave_space)
{
  gj_assert(page);

  const double dx = hadj->get_page_size();
  const double dy = vadj->get_page_size();

  Gdk::Rectangle rect = parent.get_rectangle(*page);

  Gdk::Point point(rect.get_x(), rect.get_y());

  if(leave_space)
    point = Gdk::Point(point.get_x() - 10, point.get_y() - 10);

  const double x = point.get_x() - fx*dx,
    y = point.get_y() - fy*dy;

  LOG(DEBUG) << "Scrolling to position "
             << x << ", " << y;

  hadj->set_value(x);
  vadj->set_value(y);
}

Glib::PropertyProxy<Rectangle> ScrollHandler::property_current_rectangle()
{
  return prop_current_rectangle.get_proxy();
}

Glib::PropertyProxy_ReadOnly<Rectangle> ScrollHandler::property_current_rectangle() const
{
  return Glib::PropertyProxy_ReadOnly<Rectangle>(this,
                                                 "current-rectangle");
}

Glib::PropertyProxy<PageWidget*> ScrollHandler::property_current_page()
{
  return prop_current_page.get_proxy();
}

Glib::PropertyProxy_ReadOnly<PageWidget*> ScrollHandler::property_current_page() const
{
  return Glib::PropertyProxy_ReadOnly<PageWidget*>(this,
                                                   "current-page");
}

Gdk::Point ScrollHandler::get_center_point() const
{
  return Gdk::Point(hadj->get_value() + hadj->get_page_size() / 2,
                    vadj->get_value() + vadj->get_page_size() / 2);
}

void ScrollHandler::on_adjustment_changed()
{
  property_current_rectangle().set_value(compute_current_rectangle());

  PageWidget* current_page =
    compute_current_page();

  if(current_page != property_current_page().get_value())
  {
    property_current_page().set_value(current_page);
  }
}

PageWidget* ScrollHandler::compute_current_page() const
{
  //TODO: implement
  const Rectangle current_rect(property_current_rectangle().get_value());
  PageWidget* current_page = property_current_page().get_value();


  double current_area = 0;

  if(current_page)
  {
    Rectangle rect = parent.get_rectangle(*current_page);

    gj_assert(rect.get_area() > 0);

    current_area = current_rect.intersect(rect).get_area() / rect.get_area();
  }

  for(auto page : parent.get_page_widgets())
  {
    Rectangle rect = parent.get_rectangle(*page);
    gj_assert(rect.get_area() > 0);

    if(rect.is_above(current_rect))
      continue;
    else if(rect.is_below(current_rect))
      break;

    double area =
      current_rect.intersect(parent.get_rectangle(*page)).get_area() / rect.get_area();

    if(area > current_area)
    {
      current_page = page;
      current_area = area;
    }
  }

  if(current_page)
  {
    LOG(DEBUG) << "Current page changed to number "
               << current_page->get_page()->get_number();
  }

  return current_page;
}

