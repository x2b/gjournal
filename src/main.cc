#include <gtkmm.h>

#include <cairomm/cairomm.h>

#include "gui/Application.hh"
#include "gui/JournalWidget.hh"
#include "gui/MainWindow.hh"

#include "model/Document.hh"

#include "util/Log.hh"


int main(int argc, char *argv[])
{
  Glib::RefPtr<Application> app =
    Application::create(argc, argv, "org.gnome.gjournal");

  return app->run();
}
