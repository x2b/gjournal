#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <gtkmm/builder.h>
#include <gtkmm/applicationwindow.h>

#include "model/Document.hh"

#include "gui/DocumentHandler.hh"
#include "gui/DragHandler.hh"
#include "gui/MainMenu.hh"
#include "gui/PositionWidget.hh"
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
  Glib::RefPtr<Gtk::Builder> get_builder();

  DocumentHandler& get_document_handler();

  void read_document(Glib::RefPtr<Gio::File> file);

  virtual ~MainWindow();

private:
  Glib::RefPtr<Gtk::Builder> window_builder;
  Glib::RefPtr<Gio::SimpleActionGroup> group_win;
  Gtk::Stack* stack;
  ZoomWidget* zoom_widget;
  PositionWidget* position_widget;
  DocumentHandler doc_handler;
  DragHandler drag_handler;
  MainMenu main_menu;
};

#endif /* MAINWINDOW_HH */
