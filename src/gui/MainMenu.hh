#ifndef MAINMENU_HH
#define MAINMENU_HH

#include <giomm/simpleaction.h>

#include <gtkmm/builder.h>

class JournalWidget;
class MainWindow;

class MainMenu
{
public:
  MainMenu(MainWindow& window);

private:
  void on_open_action_activated();
  void on_print_action_activated();

  void on_active_journal_changed();

  void on_action_dual_activated();
  void on_action_odd_left_activated();

  void create_menu();

  void add_menu(const Glib::ustring& menu_name,
                const Glib::ustring& button_name);

  Glib::RefPtr<Gtk::Builder> window_builder;
  Glib::RefPtr<Gio::SimpleAction> act_dual, act_odd_left;

  MainWindow& main_window;
  JournalWidget* current_journal;
};


#endif /* MAINMENU_HH */
