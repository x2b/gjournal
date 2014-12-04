#include <gtkmm.h>

#include <cairomm/cairomm.h>

#include "gui/Application.hh"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Application> app =
    Application::create(argc, argv, "org.gnome.gjournal");

  return app->run();
}
