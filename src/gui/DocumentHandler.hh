#ifndef DOCUMENTHANDLER_HH
#define DOCUMENTHANDLER_HH

#include <vector>

#include <glibmm/object.h>

#include "gui/JournalWidget.hh"

#include "model/Document.hh"

namespace Gtk
{
  class Stack;
}

class DocumentHandler : public Glib::Object
{
public:
  DocumentHandler();

  typedef sigc::signal<void, JournalWidget*> type_signal_document;

  JournalWidget* add_document(DocumentRef doc);

  type_signal_document signal_document_added();
  type_signal_document signal_document_removed();
  type_signal_document signal_document_activated();

  void set_stack(Gtk::Stack* stack);

  Glib::PropertyProxy_ReadOnly<JournalWidget*> property_active_journal()
  {
    return Glib::PropertyProxy_ReadOnly<JournalWidget*>(this,
							"active-journal");
  }
  
private:
  void on_visible_child_changed();

  Gtk::Stack* stack;
  std::vector<JournalWidget*> journals;
  sigc::connection stack_connection;

  Glib::Property<JournalWidget*> prop_active_journal;
  
  type_signal_document sig_doc_added,
    sig_doc_removed;

};

#endif
