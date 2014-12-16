#include <gtkmm.h>

#include <cairomm/cairomm.h>

#include "gui/Application.hh"

int main(int argc, char *argv[])
{
  Glib::RefPtr<Application> app =
    Application::create();

  return app->run(argc, argv);
}
