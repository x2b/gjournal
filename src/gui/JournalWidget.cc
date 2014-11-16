#include "JournalWidget.hh"

#include "gui/PageWidget.hh"

JournalWidget::JournalWidget(DocumentRef _doc)
  : doc(_doc),
    viewport(nullptr)
{
  viewport = new Gtk::Viewport(get_hadjustment(),
                               get_vadjustment());

  viewport->add(page_layout);
  add(*viewport);

  for(PageRef& page : doc->get_pages())
  {
    PageWidget* widget = new PageWidget(page);
    page_layout.add(*widget);
  }
}

JournalWidget::~JournalWidget()
{
  delete viewport;
}
