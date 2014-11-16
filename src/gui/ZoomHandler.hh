#ifndef ZOOMHANDLER_HH
#define ZOOMHANDLER_HH

#include <giomm/menu.h>

#include <gtkmm/hvbox.h>
#include <gtkmm/entry.h>
#include <gtkmm/popover.h>
#include <gtkmm/builder.h>

class ZoomHandler : public Gtk::VBox
{
public:
  ZoomHandler(BaseObjectType* cobject,
              const Glib::RefPtr<Gtk::Builder>& refBuilder);
  
private:
  void on_icon_pressed(Gtk::EntryIconPosition, const GdkEventButton*);
  void on_activated();
  void create_levels();

  Glib::RefPtr<Gio::Menu> menu;
  Gtk::Entry entry;
  Gtk::Popover popover;
  
};

#endif
