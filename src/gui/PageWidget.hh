#ifndef PAGEWIDGET_HH
#define PAGEWIDGET_HH

#include <gtkmm/drawingarea.h>

#include "model/Page.hh"

class JournalWidget;

/**
 * @brief A widget containing a single Page of a Document
 */
class PageWidget : public Gtk::DrawingArea
{
public:
  PageWidget(PageRef page, JournalWidget* parent);

  void on_zoom_level_changed();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  
  void update_size_request();

private:
  PageRef page;
  JournalWidget* parent;
};

typedef std::shared_ptr<PageWidget> PageWidgetRef;

#endif
