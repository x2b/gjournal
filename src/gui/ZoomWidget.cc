#include "ZoomWidget.hh"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "gui/MainWindow.hh"
#include "gui/ZoomHandler.hh"
#include "gui/ZoomLevel.hh"

#include "util/Error.hh"
#include "util/Log.hh"

ZoomWidget::ZoomWidget(BaseObjectType* cobject,
                       const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::VBox(cobject),
    menu(Gio::Menu::create()),
    entry(),
    popover(*this),
    builder(ref_builder),
    main_window(nullptr),
    handler(nullptr)
{
  using namespace std::placeholders;

  entry.set_icon_from_icon_name("go-down-symbolic",
                                Gtk::ENTRY_ICON_SECONDARY);

  pack_start(entry, true, false, 0);

  entry.signal_icon_press().connect(std::bind(&ZoomWidget::on_icon_pressed,
                                              this, _1, _2));

  entry.signal_activate().connect(std::bind(&ZoomWidget::on_entry_activated,
                                            this));

  popover.bind_model(menu);
}

void ZoomWidget::on_icon_pressed(Gtk::EntryIconPosition pos,
                                  const GdkEventButton* button)
{
  popover.set_pointing_to(entry.get_icon_area(Gtk::ENTRY_ICON_SECONDARY));

  popover.show();
}

void ZoomWidget::on_entry_activated()
{
  TRACE;

  std::istringstream is(entry.get_text());

  double val;

  if(not(is >> val))
    return;

  LOG(DEBUG) << "entry value: " << val;

  if(handler)
    handler->set_zoom_level(val / 100.);
}

void ZoomWidget::create_menu()
{
  TRACE;

  Glib::RefPtr<Glib::Object> obj = builder->get_object("menu_zoom");


  menu->append_section("", Glib::RefPtr<Gio::Menu>::cast_dynamic(obj));

  auto level_section = Gio::Menu::create();

  for(const ZoomLevel& level: levels)
  {
    std::ostringstream str;

    str << "win.zoom(" << std::scientific << level.level << ")";

    level_section->append_item(Gio::MenuItem::create(level.name, str.str()));
  }

  menu->append_section("", level_section);
}

void ZoomWidget::set_window(MainWindow* main_window_)
{
  gj_assert(main_window_);

  main_window = main_window_;

  using namespace std::placeholders;

  auto act = Gio::SimpleAction::create("zoom",
                                       Glib::Variant<double>::variant_type());

  act->signal_activate().connect(std::bind(&ZoomWidget::on_zoom_action_activated, this, _1));

  main_window_->add_action(act);

  main_window_->add_action_with_parameter("zoom-fit-page", std::bind(&ZoomWidget::on_zoom_fit_page, this));
  main_window_->add_action_with_parameter("zoom-fit-width", std::bind(&ZoomWidget::on_zoom_fit_width, this));

  create_menu();

  main_window->get_document_handler()
    .property_active_journal().signal_changed()
    .connect(std::bind(&ZoomWidget::on_active_journal_changed, this));
}

void ZoomWidget::on_active_journal_changed()
{
  gj_assert(main_window);

  JournalWidget* journal =
    main_window->get_document_handler()
    .property_active_journal().get_value();

  set_visible(!!(journal));

  set_handler(journal ? &(journal->get_zoom_handler()) : nullptr);
}

void ZoomWidget::set_handler(ZoomHandler* handler_)
{
  LOG(DEBUG) << "ZoomWidget::set_handler";

  if(handler_ == handler)
    return;

  handler = handler_;

  std::function<void()> func = std::bind(&ZoomWidget::on_zoom_level_changed, this);

  if(handler)
  {
    LOG(DEBUG) << "ZoomWidget::set_handler: Creating connection";

    handler_connection = handler->property_zoom_level().signal_changed().connect(func);
    set_label();
  }
  else
  {
    handler_connection.disconnect();
  }
}

void ZoomWidget::on_zoom_action_activated(const Glib::VariantBase& val_variant)
{
  Glib::Variant<double> val_double_variant =
    Glib::VariantBase::cast_dynamic<Glib::Variant<double>>(val_variant);

  gj_assert(handler);

  double val_double = val_double_variant.get();

  LOG(DEBUG) << "ZoomWidget::on_zoom_action_activated: " << val_double;

  handler->set_zoom_level(val_double);

}

void ZoomWidget::on_zoom_fit_page()
{
  LOG(DEBUG) << "ZoomWidget::on_zoom_fit_page";

  gj_assert(handler);

  handler->zoom_fit_page();
}

void ZoomWidget::on_zoom_fit_width()
{
  LOG(DEBUG) << "ZoomWidget::on_zoom_fit_width";

  gj_assert(handler);

  handler->zoom_fit_width();
}

void ZoomWidget::on_zoom_level_changed()
{
  set_label();
}

void ZoomWidget::set_label()
{
  LOG(DEBUG) << "ZoomWidget::set_label";

  gj_assert(handler);

  float val = 100 * handler->property_zoom_level().get_value();

  // a small hack to make sure <= 2 decimal
  // points are displayed
  val = int(val * 100) / 100.0f;

  entry.set_text(Glib::ustring::compose("%1 %%", val));

  int l = Glib::ustring("100.00 %").size();

  entry.set_max_width_chars(l + 3);
  entry.set_width_chars(l + 3);
}
