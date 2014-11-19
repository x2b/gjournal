#ifndef ZOOMHANDLER_HH
#define ZOOMHANDLER_HH

#include <giomm/simpleactiongroup.h>
#include <giomm/menu.h>
#include <giomm/actionmap.h>
#include <giomm/application.h>

#include <gtkmm/hvbox.h>
#include <gtkmm/entry.h>
#include <gtkmm/popover.h>
#include <gtkmm/builder.h>

class MainWindow;

class ZoomHandler : public Gtk::VBox
{
public:
  ZoomHandler(BaseObjectType* cobject,
              const Glib::RefPtr<Gtk::Builder>& ref_builder);

  void set_window(MainWindow* window);

private:
  void on_icon_pressed(Gtk::EntryIconPosition, const GdkEventButton*);
  void on_entry_activated();
  void on_zoom_level_changed(const Glib::VariantBase& value);
  void on_zoom_fit_page();
  void on_zomm_fit_width();

  void create_menu();

  Glib::RefPtr<Gio::Menu> menu;
  Gtk::Entry entry;
  Gtk::Popover popover;
  Glib::RefPtr<Gtk::Builder> builder;
};

#endif
