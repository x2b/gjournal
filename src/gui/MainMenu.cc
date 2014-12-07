#include "MainMenu.hh"

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/messagedialog.h>

#include "gui/MainWindow.hh"
#include "gui/PrintOperation.hh"

#include "util/Error.hh"
#include "util/Log.hh"

MainMenu::MainMenu(MainWindow& window)
  : main_window(window),
    current_journal(nullptr)
{
  window_builder = main_window.get_builder();


  main_window.get_document_handler()
    .property_active_journal().signal_changed()
    .connect(std::bind(&MainMenu::on_active_journal_changed, this));

  create_menu();
}

void MainMenu::on_open_action_activated()
{
  Glib::RefPtr<Gtk::FileFilter> filter
    = Gtk::FileFilter::create();

  filter->set_name("Xournal file");
  filter->add_pattern("*.xoj");

  Gtk::FileChooserDialog dlg(main_window,
                             Glib::ustring("Select File"));

  dlg.add_filter(filter);

  auto ok_button = dlg.add_button("Open", Gtk::RESPONSE_ACCEPT);
  dlg.add_button("Cancel", Gtk::RESPONSE_CANCEL);

  ok_button->set_can_default();
  ok_button->set_receives_default();
  dlg.set_default(*ok_button);
  dlg.set_select_multiple(false);

  if(dlg.run() == Gtk::RESPONSE_ACCEPT)
  {
    dlg.hide();

    main_window.read_document(dlg.get_file());
  }
}

void MainMenu::on_print_action_activated()
{
  TRACE;

  JournalWidget* active_journal
    = main_window.get_document_handler()
    .property_active_journal().get_value();

  if(not(active_journal))
    return;

  auto op =
    PrintOperation::create(active_journal->get_document());

  op->run(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG, main_window);
}

void MainMenu::create_menu()
{
  using namespace std::placeholders;

  add_menu("menu_file", "file_button");
  add_menu("menu_view", "view_button");

  auto group_win = main_window.get_action_group();

  group_win->add_action_with_parameter("open",
                                       std::bind(&MainMenu::on_open_action_activated,
                                                 this));

  group_win->add_action_with_parameter("print",
                                       std::bind(&MainMenu::on_print_action_activated, this));

  act_dual =
    group_win->add_action_bool("dual",
                               std::bind(&MainMenu::on_action_dual_activated,
                                         this),
                               false);

  act_odd_left =
    group_win->add_action_bool("odd-left",
                               std::bind(&MainMenu::on_action_odd_left_activated,
                                         this),
                               false);
}

void MainMenu::add_menu(const Glib::ustring& menu_name,
                        const Glib::ustring& button_name)
{
  Glib::RefPtr<Glib::Object> obj =
    window_builder->get_object(menu_name);

  gj_assert(obj);

  Glib::RefPtr<Gio::Menu> menu =
    Glib::RefPtr<Gio::Menu>::cast_dynamic(obj);

  Gtk::MenuButton* button = nullptr;

  window_builder->get_widget(button_name, button);

  gj_assert(button);

  button->set_menu_model(menu);
}


void MainMenu::on_action_dual_activated()
{
  TRACE;

  if(not(current_journal))
  {
    return;
  }

  bool active = false;
  act_dual->get_state(active);
  act_dual->change_state(not(active));

  active = not(active);

  current_journal->get_layout()
    .property_dual().set_value(active);

  act_odd_left->set_enabled(active);
}

void MainMenu::on_action_odd_left_activated()
{
  TRACE;

  if(not(current_journal))
  {
    return;
  }

  bool active = false;
  act_odd_left->get_state(active);
  act_odd_left->change_state(not(active));

  active = not(active);

  current_journal->get_layout()
    .property_odd_left().set_value(active);
}

void MainMenu::on_active_journal_changed()
{
  TRACE;

  current_journal =
    main_window.get_document_handler()
    .property_active_journal().get_value();

  if(not(current_journal))
  {
    return;
  }

  bool dual = current_journal->get_layout()
    .property_dual().get_value();

  act_dual->change_state(dual);

  act_odd_left->set_enabled(dual);

  act_odd_left->change_state(current_journal->get_layout()
                             .property_odd_left().get_value());
}

