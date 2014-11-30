#include "DocumentHandler.hh"

#include <gtkmm/stack.h>

#include "util/Error.hh"

DocumentHandler::DocumentHandler()
  : Glib::ObjectBase(typeid(DocumentHandler)),
    stack(nullptr),
    prop_active_journal(*this, "active-journal", nullptr)
{

}

JournalWidget* DocumentHandler::add_document(DocumentRef doc,
					     bool make_active)
{
  gj_assert(stack);
  gj_assert(doc);

  JournalWidget* widget = new JournalWidget(doc);

  widget->set_hexpand(true);
  widget->set_vexpand(true);
  widget->show_all();

  journals.push_back(widget);

  signal_document_added().emit(widget);

  Glib::ustring title = widget->get_title();

  stack->add(*widget, title, title);

  if(make_active)
  {
    stack->property_visible_child() = widget;
  }

  return widget;
}

DocumentHandler::type_signal_document
DocumentHandler::signal_document_added()
{
  return sig_doc_added;
}

DocumentHandler::type_signal_document
DocumentHandler::signal_document_removed()
{
  return sig_doc_removed;
}

void DocumentHandler::set_stack(Gtk::Stack* stack_)
{
  if(stack == stack_)
    return;

  stack = stack_;

  auto func = std::bind(&DocumentHandler::on_visible_child_changed,
			this);

  if(stack)
  {
    stack_connection =
      stack->property_visible_child().signal_changed().connect(func);
  }
  else
  {
    stack_connection.disconnect();
  }
}

void DocumentHandler::on_visible_child_changed()
{
  gj_assert(stack);

  Gtk::Widget* widget = stack->property_visible_child().get_value();

  for(auto journal : journals)
  {
    if(journal == widget)
    {
      prop_active_journal = journal;
      break;
    }
  }

}
