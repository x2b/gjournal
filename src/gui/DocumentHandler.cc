#include "DocumentHandler.hh"

#include <gtkmm/stack.h>

#include "gui/MainWindow.hh"

#include "util/Error.hh"
#include "util/Log.hh"

DocumentHandler::DocumentHandler()
  : Glib::ObjectBase(typeid(DocumentHandler)),
    stack(nullptr),
    main_window(nullptr),
    prop_active_journal(*this, "active-journal", nullptr)
{

}

JournalWidget* DocumentHandler::add_document(DocumentRef doc,
                                             bool make_active)
{
  gj_assert(stack);
  gj_assert(doc);

  const Glib::ustring uri = doc->get_uri();
  JournalWidget* widget = nullptr;

  if(not(uri.empty()))
  {
    auto it = journals_by_uri.find(uri);

    if(it != journals_by_uri.end())
      widget = it->second;
  }

  if(not(widget))
  {
    widget = Gtk::manage(new JournalWidget(doc));

    widget->set_hexpand(true);
    widget->set_vexpand(true);
    widget->show_all();

    journals.push_back(widget);

    if(not(uri.empty()))
    {
      journals_by_uri.insert(std::make_pair(uri, widget));
    }

    signal_document_added().emit(widget);

    Glib::ustring title = widget->get_title();

    stack->add(*widget, title, title);
  }

  if(make_active)
  {
    set_active_journal(widget);
  }

  act_close_journal->set_enabled(journals.size() > 0);

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

void DocumentHandler::setup(MainWindow* main_window_,
                            Gtk::Stack* stack_)
{
  main_window = main_window_;
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

  act_prev_journal =
    main_window->add_action_with_parameter(
      "prev-journal",
      std::bind(&DocumentHandler::on_action_prev_journal_activated,
                this));

  act_next_journal =
    main_window->add_action_with_parameter(
      "next-journal",
      std::bind(&DocumentHandler::on_action_next_journal_activated,
                this));

  act_close_journal =
    main_window->add_action_with_parameter(
      "close-current-journal",
      std::bind(&DocumentHandler::on_action_close_current_journal_activated,
                this));

}

void DocumentHandler::on_action_close_current_journal_activated()
{
  TRACE;

  gj_assert(stack);

  auto it = std::find(journals.begin(),
                      journals.end(),
                      property_active_journal().get_value());

  if(it == journals.end())
    return;

  JournalWidget* widget =
    property_active_journal().get_value();

  signal_document_removed().emit(widget);

  stack->remove(*widget);

  journals.erase(it);

  for(auto v : journals_by_uri)
  {
    if(v.second == widget)
    {
      journals_by_uri.erase(v.first);
      break;
    }
  }

  if(journals.size() == 0)
    set_active_journal(nullptr);

  act_close_journal->set_enabled(journals.size() > 0);
}

void DocumentHandler::on_visible_child_changed()
{
  gj_assert(stack);

  Gtk::Widget* widget = stack->property_visible_child().get_value();

  auto it = std::find(journals.begin(),
                      journals.end(),
                      widget);

  if(it != journals.end())
  {
    prop_active_journal = *it;
  }
}

void DocumentHandler::set_active_journal(JournalWidget* journal)
{
  gj_assert(stack);

  prop_active_journal.set_value(journal);

  stack->property_visible_child().set_value(journal);
}

void DocumentHandler::on_action_next_journal_activated()
{
  TRACE;

  auto it = std::find(journals.begin(),
                      journals.end(),
                      property_active_journal().get_value());

  if(it == journals.end())
    return;

  if(++it == journals.end())
    it = journals.begin();

  set_active_journal(*it);
}

void DocumentHandler::on_action_prev_journal_activated()
{
  TRACE;

  auto it = std::find(journals.begin(),
                      journals.end(),
                      property_active_journal().get_value());

  if(it == journals.end())
    return;

  if(it == journals.begin())
    it = --journals.end();
  else
    --it;


  set_active_journal(*it);
}
