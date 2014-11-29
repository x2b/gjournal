#include "Application.hh"

#include <giomm/menumodel.h>

#include <gtkmm/papersize.h>

#include "gui/MainWindow.hh"
#include "util/Log.hh"

Application::Application(int& argc,
                         char**& argv,
                         const Glib::ustring& application_id,
                         Gio::ApplicationFlags flags)
  : Gtk::Application(argc, argv, application_id, flags),
    window(nullptr)
{

}

Glib::RefPtr<Application> Application::create(int& argc,
                                              char**& argv,
                                              const Glib::ustring& application_id,
                                              Gio::ApplicationFlags flags)
{
  return Glib::RefPtr<Application>(new Application(argc,
                                                   argv,
                                                   application_id,
                                                   flags));
}

void Application::on_startup()
{
  LOG(DEBUG) << "Application::on_startup";

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

  for (int i = 0; i < 2; ++i)
  {

    DocumentRef doc = Document::create();

    Gtk::PaperSize paperSize(Gtk::PAPER_NAME_A4);

    PageRef page = doc->appendPage(paperSize.get_width(Gtk::UNIT_POINTS),
                                   paperSize.get_height(Gtk::UNIT_POINTS),
                                   1);

    if(i == 0)
      page->set_background_type(Page::BackgroundType::LINED);
    else
      page->set_background_type(Page::BackgroundType::RULED);

    for(int i = 0; i < 10; ++i)
    {
      doc->appendPage(paperSize.get_width(Gtk::UNIT_POINTS),
                      paperSize.get_height(Gtk::UNIT_POINTS),
                      i + 2);
    }

    window->get_document_handler().add_document(doc);
  }

  window->set_default_size(800, 600);
  window->set_position(Gtk::WIN_POS_CENTER);

  auto act_quit = Gio::SimpleAction::create("quit");

  act_quit->signal_activate().connect(std::bind(&Application::on_quit,
						this));

  add_action(act_quit);
}

void Application::on_activate()
{
  LOG(DEBUG) << "Application::on_activate";

  Gtk::Application::on_activate();

  window->show_all();
}

void Application::on_quit()
{
  LOG(DEBUG) << "Application::on_quit";
}
