#include "MainWindow.hh"

#include <giomm/menu.h>

#include <gtkmm/messagedialog.h>
#include <gtkmm/stack.h>

#include "gui/JournalWidget.hh"

#include "io/XojReader.hh"

#include "util/Error.hh"
#include "util/Log.hh"
#include "util/ReadError.hh"

MainWindow::MainWindow(MainWindow::BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::ApplicationWindow(cobject),
    window_builder(ref_builder),
    stack(nullptr),
    zoom_widget(nullptr),
    position_widget(nullptr),
    drag_handler(*this),
    main_menu(*this)
{
  LOG(DEBUG) << "Created main window";

  window_builder->get_widget("stack", stack);

  doc_handler.setup(this, stack);

  window_builder->get_widget_derived("zoom", zoom_widget);
  window_builder->get_widget_derived("position_widget",
                                     position_widget);

  zoom_widget->set_window(this);
  position_widget->set_window(this);

  zoom_widget->show_all();
}

void MainWindow::read_document(Glib::RefPtr<Gio::File> file)
{
  XojReader reader;
  DocumentRef doc;

  try
  {
    doc = reader.read_from_file(file->get_uri());
  }
  catch(ReadError& e)
  {
    Gtk::MessageDialog error_dlg(*this, e.what(), false,
                                 Gtk::MESSAGE_ERROR,
                                 Gtk::BUTTONS_OK);

    error_dlg.set_title("Read error");

    error_dlg.run();
  }

  //JournalWidget* journal =
  get_document_handler().add_document(doc);
}


DocumentHandler& MainWindow::get_document_handler()
{
  return doc_handler;
}

Glib::RefPtr<Gtk::Builder> MainWindow::get_builder()
{
  return window_builder;
}

MainWindow::~MainWindow()
{
  TRACE;
  delete stack;
  delete zoom_widget;
  delete position_widget;
}
