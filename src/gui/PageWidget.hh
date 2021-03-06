#ifndef PAGEWIDGET_HH
#define PAGEWIDGET_HH

#include <gtkmm/drawingarea.h>

#include "gui/SurfaceBuffer.hh"

#include "model/Page.hh"

class JournalWidget;

/**
 * @brief A widget containing a single Page of a Document
 */
class PageWidget : public Gtk::DrawingArea
{
public:
  PageWidget(PageRef page, JournalWidget* parent);
  virtual ~PageWidget();

  void on_zoom_level_changed();

  PageRef get_page();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  void update_size_request();

private:
  PageRef page;
  SurfaceBuffer buffer;
  JournalWidget* parent;
};

typedef std::shared_ptr<PageWidget> PageWidgetRef;

#endif
