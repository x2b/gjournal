#ifndef JOURNALWIDGET_HH
#define JOURNALWIDGET_HH

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>

#include "model/Document.hh"

#include "gui/PageLayout.hh"

class JournalWidget : public Gtk::ScrolledWindow
{
public:
  JournalWidget(DocumentRef doc);
  ~JournalWidget();

private:
  PageLayout page_layout;
  DocumentRef doc;
  Gtk::Viewport* viewport;
};

#endif
