#include "PageWidget.hh"

#include <iostream>
using namespace std;

PageWidget::PageWidget(PageRef page)
  : Gtk::DrawingArea(), page(page)
{
  set_events(Gdk::ALL_EVENTS_MASK);
  set_size_request(page->get_width(), page->get_height());
}

bool PageWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  page->draw(cr);

  auto alloc = get_allocation();

  return true;
}

