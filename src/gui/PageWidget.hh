#ifndef PAGEWIDGET_HH
#define PAGEWIDGET_HH

#include <gtkmm/drawingarea.h>

#include "model/Page.hh"

class PageWidget : public Gtk::DrawingArea
{
public:
  PageWidget(PageRef page);

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
  PageRef page;
};

typedef std::shared_ptr<PageWidget> PageWidgetRef;

#endif
