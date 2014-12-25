#include "Application.hh"

#include <giomm/menumodel.h>

#include <gtkmm/papersize.h>

#include "gui/MainWindow.hh"

#include "util/Error.hh"
#include "util/Log.hh"

Application::Application()
  : Gtk::Application("org.gnome.gjournal"),
    window(nullptr)
{
  set_flags(Gio::APPLICATION_HANDLES_OPEN);
}

Glib::RefPtr<Application> Application::create()
{
  return Glib::RefPtr<Application>(new Application());
}

void Application::on_startup()
{
  TRACE;

  Gtk::Application::on_startup();

  Glib::RefPtr<Gtk::Builder> win_builder; //, menu_builder;

  try
  {
    win_builder = Gtk::Builder::create_from_resource("/org/gnome/gjournal/ui/main_window.ui");

    if(win_builder)
      win_builder->add_from_resource("/org/gnome/gjournal/ui/menus.ui");
  }
  catch(Gtk::BuilderError& error)
  {
    LOG(ERROR) << "Error loading glade file: " << error.what();
    return;
  }

  win_builder->get_widget_derived("main_window", window);

  if(not(window))
  {
    LOG(ERROR) << "Could not find main window";
    return;
  }

  add_window(*window);

  for (int i = 0; i < 1; ++i)
  {

    DocumentRef doc = Document::create();

    Gtk::PaperSize paperSize(Gtk::PAPER_NAME_A4);

    PageRef page = doc->append_page(paperSize.get_width(Gtk::UNIT_POINTS),
                                    paperSize.get_height(Gtk::UNIT_POINTS),
                                    1);

    if(i == 0)
      page->get_background().set_style(Background::LINED);
    else
      page->get_background().set_style(Background::RULED);

    for(int i = 0; i < 10; ++i)
    {
      doc->append_page(paperSize.get_width(Gtk::UNIT_POINTS),
                       paperSize.get_height(Gtk::UNIT_POINTS),
                       i + 2);
    }

    window->get_document_handler().add_document(doc);
  }

  window->set_default_size(800, 600);
  window->set_position(Gtk::WIN_POS_CENTER);

  window->signal_hide().connect(std::bind(&Application::on_window_hide, this, window));

  auto act_quit = Gio::SimpleAction::create("quit");

  act_quit->signal_activate().connect(std::bind(&Application::on_quit,
                                                this));

  window->show_all();

  add_action(act_quit);

  const std::map<std::string, std::string>
    accels({{"win.open", "<Primary>o"},
        {"win.print", "<Primary>p"},
        {"win.next-journal", "<Primary>Tab"},
        {"win.prev-journal", "<Shift><Primary>Tab"},
        {"win.close-current-journal", "<Primary>w"},
        {"app.quit", "<Primary>q"}});

  for(auto& accel : accels)
  {
    set_accel_for_action(accel.first, accel.second);
  }
}

void Application::on_activate()
{
  TRACE;

  Gtk::Application::on_activate();

  window->show_all();
}

void Application::on_open(const Gio::Application::type_vec_files& files,
                          const Glib::ustring& hint)
{
  gj_assert(window);

  for(auto file : files)
  {
    window->read_document(file);
  }

  window->present();
}

void Application::on_window_hide(MainWindow* window_)
{
  TRACE;

  if(window == window_)
  {
    window = nullptr;
  }

  delete window_;
}

void Application::on_quit()
{
  TRACE;

  delete window;
  window = nullptr;
}

Application::~Application()
{
  TRACE;
}
