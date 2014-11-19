#include "ZoomHandler.hh"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "gui/MainWindow.hh"
#include "util/Log.hh"

struct ZoomLevel
{
  ZoomLevel(std::string _name, double _level)
    : name(_name), level(_level)
  {}

  std::string name;
  double level;
};


const std::vector<ZoomLevel> levels({ZoomLevel("50%", 0.5),
                                     ZoomLevel("70%", 0.7071067811),
                                     ZoomLevel("85%", 0.8408964152),
                                     ZoomLevel("100%", 1.0),
                                     ZoomLevel("125%", 1.1892071149),
                                     ZoomLevel("150%", 1.4142135623),
                                     ZoomLevel("175%", 1.6817928304),
                                     ZoomLevel("200%", 2.0)});

ZoomHandler::ZoomHandler(BaseObjectType* cobject,
                         const Glib::RefPtr<Gtk::Builder>& ref_builder)
  : Gtk::VBox(cobject),
    menu(Gio::Menu::create()),
    entry(),
    popover(*this),
    builder(ref_builder)
{
  using namespace std::placeholders;

  entry.set_icon_from_icon_name("go-down-symbolic",
                                Gtk::ENTRY_ICON_SECONDARY);

  pack_start(entry, true, false, 0);

  entry.signal_icon_press().connect(std::bind(&ZoomHandler::on_icon_pressed,
                                              this, _1, _2));

  entry.signal_activate().connect(std::bind(&ZoomHandler::on_entry_activated,
                                            this));

  popover.bind_model(menu);
}

void ZoomHandler::on_icon_pressed(Gtk::EntryIconPosition pos,
                                  const GdkEventButton* button)
{
  popover.set_pointing_to(entry.get_icon_area(Gtk::ENTRY_ICON_SECONDARY));

  popover.set_sensitive(true);
  popover.show();
}

void ZoomHandler::on_entry_activated()
{
  LOG(DEBUG) << "ZoomHandler::on_entry_activated";

  std::istringstream is(entry.get_text());

  double val;

  if(!(is >> val))
    return;

  LOG(DEBUG) << "entry value: " << val;
}

void ZoomHandler::create_menu()
{
  LOG(DEBUG) << "Creating zoom menu";

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

void ZoomHandler::set_window(MainWindow* window)
{
  using namespace std::placeholders;

  auto group = window->get_action_group();

  auto act = Gio::SimpleAction::create("zoom",
                                       Glib::Variant<double>::variant_type());

  act->signal_activate().connect(std::bind(&ZoomHandler::on_zoom_level_changed, this, _1));

  group->add_action(act);

  group->add_action_with_parameter("zoom-fit-page", std::bind(&ZoomHandler::on_zoom_fit_page, this));
  group->add_action_with_parameter("zoom-fit-width", std::bind(&ZoomHandler::on_zoom_fit_page, this));

  create_menu();
}

void ZoomHandler::on_zoom_level_changed(const Glib::VariantBase& value)
{
  Glib::Variant<double> double_val =
    Glib::VariantBase::cast_dynamic<Glib::Variant<double>>(value);

  LOG(DEBUG) << "ZoomHandler::on_zoom_level_changed: " << double_val.get();
}

void ZoomHandler::on_zoom_fit_page()
{
  LOG(DEBUG) << "ZoomHandler::on_zoom_fit_page";
}

void ZoomHandler::on_zomm_fit_width()
{
  LOG(DEBUG) << "ZoomHandler::on_zomm_fit_width";
}

/*

static const struct {
        const gchar *name;
        float        level;
} zoom_levels[] = {
        { N_("50%"), 0.5 },
        { N_("70%"), 0.7071067811 },
        { N_("85%"), 0.8408964152 },
        { N_("100%"), 1.0 },
        { N_("125%"), 1.1892071149 },
        { N_("150%"), 1.4142135623 },
        { N_("175%"), 1.6817928304 },
        { N_("200%"), 2.0 },
        { N_("300%"), 2.8284271247 },
        { N_("400%"), 4.0 },
        { N_("800%"), 8.0 },
        { N_("1600%"), 16.0 },
        { N_("3200%"), 32.0 },
        { N_("6400%"), 64.0 }
};

        priv->entry = gtk_entry_new ();
        gtk_entry_set_icon_from_icon_name (GTK_ENTRY (priv->entry),
                                           GTK_ENTRY_ICON_SECONDARY,
                                           "go-down-symbolic");
        gtk_box_pack_start (GTK_BOX (zoom_action), priv->entry, TRUE, FALSE, 0);
        gtk_widget_show (priv->entry);

        g_signal_connect (priv->entry, "icon-press",
                          G_CALLBACK (entry_icon_press_callback),
                          zoom_action);
        g_signal_connect (priv->entry, "activate",
                          G_CALLBACK (entry_activated_cb),
                          zoom_action);
        g_signal_connect_swapped (priv->entry, "focus-out-event",
                                  G_CALLBACK (focus_out_cb),
                                  zoom_action);


        for (i = 0; i < G_N_ELEMENTS (zoom_levels); i++) {
                GMenuItem *item;
                gint       length;

                if (zoom_levels[i].level > max_scale)
                        break;

                length = g_utf8_strlen (zoom_levels[i].name, -1);
                if (length > width)
                        width = length;

                item = g_menu_item_new (zoom_levels[i].name, NULL);
                g_menu_item_set_action_and_target (item, "win.zoom",
                                                   "d", zoom_levels[i].level);
                g_menu_append_item (G_MENU (zoom_action->priv->zoom_free_section), item);
                g_object_unref (item);
        }
*/
