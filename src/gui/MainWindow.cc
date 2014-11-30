#include "MainWindow.hh"

#include <giomm/menu.h>

#include <gtkmm/filechooserdialog.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/stack.h>

#include "gui/JournalWidget.hh"
#include "io/XojReader.hh"
#include "util/Log.hh"
#include "util/ReadError.hh"

MainWindow::MainWindow(MainWindow::BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::ApplicationWindow(cobject),
    window_builder(ref_builder),
    group_win(Gio::SimpleActionGroup::create()),
    stack(nullptr),
    zoom_widget(nullptr)
{
  LOG(DEBUG) << "Created main window";

  insert_action_group("win", group_win);

  window_builder->get_widget("stack", stack);

  doc_handler.set_stack(stack);

  window_builder->get_widget_derived("zoom", zoom_widget);

  zoom_widget->set_window(this);

  create_menu();
}

void MainWindow::read_document(Glib::RefPtr<Gio::File> file)
{
  XojReader reader;
  DocumentRef doc = reader.read_from_file(file->get_uri());

  //JournalWidget* journal =
  get_document_handler().add_document(doc);
}


DocumentHandler& MainWindow::get_document_handler()
{
  return doc_handler;
}

Glib::RefPtr<Gio::SimpleActionGroup> MainWindow::get_action_group()
{
  return group_win;
}

void MainWindow::create_menu()
{
  Glib::RefPtr<Glib::Object> obj =
    window_builder->get_object("menu_actions");

  Glib::RefPtr<Gio::Menu> menu =
    Glib::RefPtr<Gio::Menu>::cast_dynamic(obj);

  Gtk::MenuButton* gears_button = nullptr;

  window_builder->get_widget("gears", gears_button);

  gears_button->set_use_popover(false);
  gears_button->set_menu_model(menu);


  group_win->add_action_with_parameter("open",
                                       std::bind(&MainWindow::on_open_action_activated,
                                                 this));
}

void MainWindow::on_open_action_activated()
{
  Glib::RefPtr<Gtk::FileFilter> filter
    = Gtk::FileFilter::create();

  filter->set_name("Xournal file");
  filter->add_pattern("*.xoj");

  Gtk::FileChooserDialog dlg(*this,
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
    try
    {
      read_document(dlg.get_file());
    }
    catch(ReadError& e)
    {
      dlg.hide();

      Gtk::MessageDialog error_dlg(*this, e.what(), false,
                                   Gtk::MESSAGE_ERROR,
                                   Gtk::BUTTONS_OK);

      error_dlg.set_title("Read error");

      error_dlg.run();
    }
  }

}

MainWindow::~MainWindow()
{

}
