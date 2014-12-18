#ifndef DOCUMENTHANDLER_HH
#define DOCUMENTHANDLER_HH

#include <vector>
#include <map>

#include <glibmm/object.h>

#include <giomm/simpleaction.h>

#include "gui/JournalWidget.hh"

#include "model/Document.hh"

namespace Gtk
{
  class Stack;
}

class MainWindow;

class DocumentHandler : public Glib::Object
{
public:
  DocumentHandler();

  typedef sigc::signal<void, JournalWidget*> type_signal_document;

  JournalWidget* add_document(DocumentRef doc,
                              bool make_active = true);

  void set_active_journal(JournalWidget* journal);

  type_signal_document signal_document_added();
  type_signal_document signal_document_removed();

  void setup(MainWindow* main_window_,
             Gtk::Stack* stack_);

  Glib::PropertyProxy_ReadOnly<JournalWidget*> property_active_journal()
  {
    return Glib::PropertyProxy_ReadOnly<JournalWidget*>(this,
                                                        "active-journal");
  }

private:
  void on_visible_child_changed();

  void on_action_next_journal_activated();
  void on_action_prev_journal_activated();
  void on_action_close_current_journal_activated();

  Gtk::Stack* stack;
  MainWindow* main_window;

  std::vector<JournalWidget*> journals;
  sigc::connection stack_connection;

  std::map<Glib::ustring,
           JournalWidget*> journals_by_uri;

  Glib::Property<JournalWidget*> prop_active_journal;

  Glib::RefPtr<Gio::SimpleAction> act_next_journal,
    act_prev_journal, act_close_journal;

  type_signal_document sig_doc_added,
    sig_doc_removed;

};

#endif
