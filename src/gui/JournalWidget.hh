#ifndef JOURNALWIDGET_HH
#define JOURNALWIDGET_HH

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>

#include "model/Document.hh"

#include "gui/PageLayout.hh"
#include "gui/ScrollHandler.hh"
#include "gui/ZoomHandler.hh"

class PageWidget;

/**
 * @brief A Gtk::ScrolledWindow containing a PageLayout
 */
class JournalWidget : public Gtk::ScrolledWindow
{
public:
  /**
   * Constructs a new JournalWidget
   *
   * @param doc The document to be displayed
   */
  JournalWidget(DocumentRef doc);
  ~JournalWidget();

  /**
   * Returns the suggested title of this JournalWidget
   */
  Glib::ustring get_title() const;

  /**
   * Returns the underlying PageLayout
   */
  PageLayout& get_layout();

  ScrollHandler& get_scroll_handler();
  ZoomHandler& get_zoom_handler();

protected:
  bool on_scroll_event(GdkEventScroll* event) override;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:

  void get_debug_msg(std::ostringstream& str);

  PageLayout page_layout;
  DocumentRef doc;
  Gtk::Viewport* viewport;
  ScrollHandler scroll_handler;
  ZoomHandler zoom_handler;

  std::vector<PageWidget*> pages;
};

#endif
