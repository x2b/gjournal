#include <gtkmm.h>

#include <cairomm/cairomm.h>

#include <gtkmm/papersize.h>

#include "model/Document.hh"

int main(int argc, char *argv[])
{
  /*
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,"");

  Gtk::Window window;
  window.set_default_size(200, 200);

  return app->run(window);
  */
  
  Glib::init();
  
  Document doc;
  
  Gtk::PaperSize paperSize("iso_a4");
  
  PageRef page = doc.appendPage(paperSize.get_width(Gtk::UNIT_POINTS),
                                paperSize.get_height(Gtk::UNIT_POINTS),
                                1);
  
  page->setBackgroundType(Page::GRAPH);
  
  auto surf = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,
                                          page->getWidth(),
                                          page->getHeight());
  
  {
    auto cr = Cairo::Context::create(surf);
    page->draw(cr);
  }
  
  surf->write_to_png("output.png");
  
  return 0;
}
