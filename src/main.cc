#include <gtkmm.h>

#include <cairomm/cairomm.h>

#include <gtkmm/papersize.h>

#include "gui/JournalWidget.hh"
#include "gui/MainWindow.hh"
#include "gui/PageLayout.hh"
#include "gui/PageWidget.hh"

#include "model/Document.hh"

#include "util/Log.hh"

int main(int argc, char *argv[])
{
  Glib::init();

  DocumentRef doc = Document::create();

  Gtk::PaperSize paperSize("iso_a4");

  PageRef page = doc->appendPage(paperSize.get_width(Gtk::UNIT_POINTS),
                                 paperSize.get_height(Gtk::UNIT_POINTS),
                                 1);

  page->set_background_type(Page::GRAPH);

  for(int i = 0; i < 10; ++i)
  {
    doc->appendPage(paperSize.get_width(Gtk::UNIT_POINTS),
                    paperSize.get_height(Gtk::UNIT_POINTS),
                    i + 2);
  }

  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,"");

  app->register_application();

  JournalWidget widget(doc);

  Glib::RefPtr< Gtk::Builder > builder;

  try
  {
    builder = Gtk::Builder::create_from_resource("/org/gnome/gjournal/ui/main_window.ui");
  }
  catch(Gtk::BuilderError& error)
  {
    LOG(ERROR) << "Error loading glade file: " << error.what() << std::endl;
    return 1;
  }

  MainWindow* window = nullptr;

  builder->get_widget_derived("main_window", window);


  if(!window)
  {
    LOG(ERROR) << "Could not find main window" << std::endl;
    return 1;
  }

  window->add_document(doc);

  //window.add(widget);
  window->show_all();

  //window.set_default_size(800, 600);

  return app->run(*window);
}
