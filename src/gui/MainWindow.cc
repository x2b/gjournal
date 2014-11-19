#include "MainWindow.hh"

#include <gtkmm/stack.h>

#include "gui/JournalWidget.hh"

#include "util/Log.hh"

MainWindow::MainWindow(MainWindow::BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::ApplicationWindow(cobject),
    builder(ref_builder),
    group_win(Gio::SimpleActionGroup::create()),
    stack(nullptr),
    handler(nullptr)
{
  LOG(DEBUG) << "Created main window";

  insert_action_group("win", group_win);

  builder->get_widget("stack", stack);

  builder->get_widget_derived("zoom", handler);

  handler->set_window(this);
}

void MainWindow::add_document(DocumentRef doc)
{
  JournalWidget* widget = new JournalWidget(doc);

  widget->set_hexpand(true);
  widget->set_vexpand(true);

  std::string name = doc->get_URI();

  if(name.empty())
    name = "untitled";

  stack->add(*widget,  name, name);
}

Glib::RefPtr<Gio::SimpleActionGroup> MainWindow::get_action_group()
{
  return group_win;
}

MainWindow::~MainWindow()
{

}
