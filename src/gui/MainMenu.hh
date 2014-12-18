#ifndef MAINMENU_HH
#define MAINMENU_HH

#include <giomm/menu.h>
#include <giomm/simpleaction.h>

#include <gtkmm/builder.h>
#include <gtkmm/recentmanager.h>

class JournalWidget;
class MainWindow;

class MainMenu
{
public:
  MainMenu(MainWindow& window);

private:
  void on_open_action_activated();
  void on_print_action_activated();

  void on_open_file_action_activated(const Glib::VariantBase &value);

  void on_active_journal_changed();

  void on_action_dual_activated();
  void on_action_odd_left_activated();

  void create_menu();
  void create_actions();

  void update_recent_menu();

  void add_menu(const Glib::ustring& menu_name,
                const Glib::ustring& button_name);

  MainWindow& main_window;

  Glib::RefPtr<Gtk::Builder> window_builder;
  Glib::RefPtr<Gio::SimpleAction> act_dual, act_odd_left;
  Glib::RefPtr<Gtk::RecentManager> recent_manager;
  Glib::RefPtr<Gio::Menu> menu_recent;

  JournalWidget* current_journal;
};


#endif /* MAINMENU_HH */
