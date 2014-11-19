#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gtkmm/builder.h>
#include <gtkmm/applicationwindow.h>

#include "model/Document.hh"

#include "gui/ZoomHandler.hh"

namespace Gtk
{
  class Stack;
}

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& ref_builder);

  void add_document(DocumentRef doc);

  Glib::RefPtr<Gio::SimpleActionGroup> get_action_group();

  virtual ~MainWindow();

private:
  Glib::RefPtr<Gtk::Builder> builder;
  Glib::RefPtr<Gio::SimpleActionGroup> group_win;
  Gtk::Stack* stack;
  ZoomHandler* handler;
};

#endif
