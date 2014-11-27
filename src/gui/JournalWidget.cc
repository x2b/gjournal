#include "JournalWidget.hh"

#include "gui/PageWidget.hh"
#include "util/Log.hh"

JournalWidget::JournalWidget(DocumentRef doc_)
  : doc(doc_),
    viewport(nullptr),
    scroll_handler(*this),
    zoom_handler(*this)
{
  viewport = new Gtk::Viewport(get_hadjustment(),
                               get_vadjustment());

  viewport->add(page_layout);
  add(*viewport);

  pages.reserve(doc->count_pages());
  
  for(PageRef& page : doc->get_pages())
  {
    PageWidget* widget = new PageWidget(page, this);
    page_layout.add(*widget);
    pages.push_back(widget);
  }
}

JournalWidget::~JournalWidget()
{
  delete viewport;
}

Glib::ustring JournalWidget::get_title() const
{
  Glib::ustring title = doc->get_URI();

  if(title.empty())
  {
    title = "untitled";
  }
  
  return title;
}

PageLayout& JournalWidget::get_layout()
{
  return page_layout;
}

ScrollHandler& JournalWidget::get_scroll_handler()
{
  return scroll_handler;
}


ZoomHandler& JournalWidget::get_zoom_handler()
{
  return zoom_handler;
}

bool JournalWidget::on_scroll_event(GdkEventScroll* event)
{
  if((event->state & GDK_CONTROL_MASK))
  {
    LOG(DEBUG) << "JournalWidget::on_scroll_event";

    if(event->direction == GDK_SCROLL_UP)
    {
      zoom_handler.zoom_in();
    }
    else if(event->direction == GDK_SCROLL_DOWN)
    {
      zoom_handler.zoom_out();
    }

    return true;
  }

  return Gtk::ScrolledWindow::on_scroll_event(event);
}
