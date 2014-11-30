#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gtkmm/builder.h>
#include <gtkmm/applicationwindow.h>

#include "model/Document.hh"

#include "gui/DocumentHandler.hh"
#include "gui/ZoomHandler.hh"
#include "gui/ZoomWidget.hh"

namespace Gtk
{
  class Stack;
}

class MainWindow : public Gtk::ApplicationWindow
{
public:
  MainWindow(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& ref_builder);

  Glib::RefPtr<Gio::SimpleActionGroup> get_action_group();
  DocumentHandler& get_document_handler();

  void read_document(Glib::RefPtr<Gio::File> file);

  virtual ~MainWindow();

private:
  void create_menu();
  void on_open_action_activated();

  Glib::RefPtr<Gtk::Builder> window_builder;
  Glib::RefPtr<Gio::SimpleActionGroup> group_win;
  Gtk::Stack* stack;
  ZoomWidget* zoom_widget;
  DocumentHandler doc_handler;
};

#endif
