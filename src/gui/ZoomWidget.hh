#ifndef ZOOMWIDGET_HH
#define ZOOMWIDGET_HH

#include <giomm/simpleactiongroup.h>
#include <giomm/menu.h>
#include <giomm/actionmap.h>
#include <giomm/application.h>

#include <gtkmm/hvbox.h>
#include <gtkmm/entry.h>
#include <gtkmm/popover.h>
#include <gtkmm/builder.h>

class MainWindow;
class ZoomHandler;

class ZoomWidget : public Gtk::VBox
{
public:
  ZoomWidget(BaseObjectType* cobject,
              const Glib::RefPtr<Gtk::Builder>& ref_builder);

  void set_window(MainWindow* window);

  void set_handler(ZoomHandler* handler);

private:
  void on_icon_pressed(Gtk::EntryIconPosition, const GdkEventButton*);
  void on_entry_activated();
  void on_zoom_action_activated(const Glib::VariantBase& value);
  void on_zoom_fit_page();
  void on_zoom_fit_width();
  void on_zoom_level_changed();
  void on_active_journal_changed();

  void create_menu();

  void set_label();

  Glib::RefPtr<Gio::Menu> menu;
  Gtk::Entry entry;
  Gtk::Popover popover;
  Glib::RefPtr<Gtk::Builder> builder;
  MainWindow* main_window;

  ZoomHandler *handler;
  sigc::connection handler_connection;
};

#endif
