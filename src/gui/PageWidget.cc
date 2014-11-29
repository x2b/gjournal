#include "PageWidget.hh"

#include "gui/JournalWidget.hh"

#include "util/Log.hh"

PageWidget::PageWidget(PageRef page, JournalWidget* parent_)
  : Gtk::DrawingArea(), page(page), parent(parent_)
{
  set_events(Gdk::ALL_EVENTS_MASK);
  update_size_request();

  auto func = std::bind(&PageWidget::on_zoom_level_changed, this);

  parent->get_zoom_handler().property_zoom_level()
    .signal_changed().connect(func);
}

bool PageWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  float zoom = parent->get_zoom_handler().get_zoom_level();

  cr->scale(zoom, zoom);

  page->draw(cr);
  return true;
}

void PageWidget::on_zoom_level_changed()
{
  TRACE;

  update_size_request();
}

void PageWidget::update_size_request()
{
  TRACE;

  float zoom = parent->get_zoom_handler().get_zoom_level();

  set_size_request(zoom * page->get_width(),
                   zoom * page->get_height());
}
