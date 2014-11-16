#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gtkmm/builder.h>
#include <gtkmm/window.h>

#include "model/Document.hh"

#include "gui/ZoomHandler.hh"

namespace Gtk
{
  class Stack;
}

class MainWindow : public Gtk::Window
{
public:
  MainWindow(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& refBuilder);

  void add_document(DocumentRef doc);

  virtual ~MainWindow();

private:
  Glib::RefPtr<Gtk::Builder> builder;
  Gtk::Stack* stack;
  ZoomHandler* handler;
};

#endif
