#include "MainWindow.hh"

#include <gtkmm/stack.h>

#include "gui/JournalWidget.hh"

#include "util/Log.hh"

MainWindow::MainWindow(MainWindow::BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& refBuilder)
  : Gtk::Window(cobject),
    builder(refBuilder),
    stack(nullptr),
    handler(nullptr)
{
  LOG(DEBUG) << "Created main window" << endl;

  refBuilder->get_widget("stack", stack);

  refBuilder->get_widget_derived("zoom", handler);
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

MainWindow::~MainWindow()
{

}
