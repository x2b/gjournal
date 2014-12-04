#ifndef POSITIONWIDGET_HH
#define POSITIONWIDGET_HH

#include <giomm/simpleaction.h>

#include <gtkmm/entry.h>
#include <gtkmm/hvbox.h>
#include <gtkmm/builder.h>

class JournalWidget;
class MainWindow;
class PageWidget;

class PositionWidget : public Gtk::Box
{
public:
  PositionWidget(BaseObjectType* cobject,
                 const Glib::RefPtr<Gtk::Builder>& ref_builder);

  void set_window(MainWindow* window);
private:
  void on_next_page_activated();
  void on_prev_page_activated();
  void on_active_journal_changed();
  void on_current_page_changed();
  void on_entry_activated();

  void update();

  void scroll_to_page_number(int no);

  MainWindow* main_window;
  JournalWidget* active_journal;
  Glib::RefPtr<Gtk::Builder> builder;
  Glib::RefPtr<Gio::SimpleAction> act_prev, act_next;
  sigc::connection handler_connection;

  Gtk::Entry *page_entry, *no_pages_entry;
};


#endif /* POSITIONWIDGET_HH */
