#include "PositionWidget.hh"

#include <gtkmm/button.h>

#include "MainWindow.hh"

#include "util/Error.hh"
#include "util/Log.hh"

// a simple predicate for searching
struct HasSameNumber
{
  HasSameNumber(int v) : val(v) {}

  bool operator() (PageWidget* page_widget)
  {
    return val == page_widget->get_page()->get_number();
  }

  int val;
};


PositionWidget::PositionWidget(BaseObjectType* cobject,
                               const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::Box(cobject),
    main_window(nullptr),
    active_journal(nullptr),
    builder(ref_builder),
    page_entry(nullptr),
    no_pages_entry(nullptr)
{
  builder->get_widget("page_entry", page_entry);
  builder->get_widget("no_pages_entry", no_pages_entry);

  gj_assert(page_entry and no_pages_entry);

  page_entry->signal_activate()
    .connect(std::bind(&PositionWidget::on_entry_activated, this));
}

void PositionWidget::set_window(MainWindow* window)
{
  TRACE;

  gj_assert(window);

  main_window = window;

 act_next =
    main_window->add_action_with_parameter("next-page",
                                           std::bind(&PositionWidget::on_next_page_activated,
                                               this));

  act_prev =
    main_window->add_action_with_parameter("prev-page",
                                           std::bind(&PositionWidget::on_prev_page_activated,
                                               this));

  window->get_document_handler()
    .property_active_journal().signal_changed()
    .connect(std::bind(&PositionWidget::on_active_journal_changed,
                       this));
}

void PositionWidget::on_next_page_activated()
{
  TRACE;

  gj_assert(active_journal);


  PageWidget* current_page =
    active_journal->get_scroll_handler()
    .property_current_page().get_value();

  gj_assert(current_page);

  scroll_to_page_number(current_page->get_page()->get_number() + 1);
}

void PositionWidget::on_prev_page_activated()
{
  TRACE;

  gj_assert(active_journal);


  PageWidget* current_page =
    active_journal->get_scroll_handler()
    .property_current_page().get_value();

  gj_assert(current_page);

  scroll_to_page_number(current_page->get_page()->get_number() - 1);
}

void PositionWidget::on_active_journal_changed()
{
  TRACE;

  gj_assert(main_window);

  JournalWidget* journal =
    main_window->get_document_handler()
    .property_active_journal().get_value();

  gj_assert(journal);

  active_journal = journal;

  auto func = std::bind(&PositionWidget::on_current_page_changed,
                        this);

  handler_connection =
    journal->get_scroll_handler()
    .property_current_page()
    .signal_changed().connect(func);

  update();
}

void PositionWidget::on_current_page_changed()
{
  update();
}

void PositionWidget::update()
{
  gj_assert(active_journal);

  PageWidget* current_page =
    active_journal->get_scroll_handler()
    .property_current_page().get_value();

  if(current_page)
  {
    act_prev->set_enabled(current_page !=
                          *(active_journal->get_page_widgets().begin()));

    act_next->set_enabled(current_page !=
                          *(active_journal->get_page_widgets().rbegin()));

    page_entry->set_text(Glib::ustring::compose("%1",
                                                current_page->get_page()->get_number() + 1));

    int no_pages = active_journal->get_document()->count_pages();
    Glib::ustring no_pages_string =
      Glib::ustring::compose("of %1", no_pages);

    int n = 0;
    while(no_pages)
    {
      ++n;
      no_pages /= 10;
    }

    no_pages_entry->set_text(no_pages_string);
    no_pages_entry->set_max_width_chars(no_pages_string.size());
    no_pages_entry->set_width_chars(no_pages_string.size());
    page_entry->set_max_width_chars(n);
    page_entry->set_max_length(n);
  }
  else
  {
    act_prev->set_enabled(false);
    act_next->set_enabled(false);
  }
}

void PositionWidget::on_entry_activated()
{
  TRACE;

  std::istringstream is(page_entry->get_text());

  int val;

  if(not(is >> val))
  {
    return;
  }

  val -= 1;

  LOG(DEBUG) << "entry value: " << val;

  gj_assert(active_journal);

  const auto& page_widgets = active_journal->get_page_widgets();

  auto it = std::find_if(page_widgets.begin(),
                         page_widgets.end(),
                         HasSameNumber(val));

  if(it != page_widgets.end())
  {
    active_journal->get_scroll_handler().scroll_to_page(*it);
  }
}

void PositionWidget::scroll_to_page_number(int no)
{
  TRACE;

  gj_assert(active_journal);

  const auto& page_widgets = active_journal->get_page_widgets();

  auto it = std::find_if(page_widgets.begin(),
                         page_widgets.end(),
                         HasSameNumber(no));


  if(it != page_widgets.end())
  {
    active_journal->get_scroll_handler().scroll_to_page(*it,
                                                        0, 0, true);
  }
}
