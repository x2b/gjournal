#ifndef APPLICATION_HH
#define APPLICATION_HH

#include <gtkmm/application.h>

class MainWindow;

class Application : public Gtk::Application
{
public:
  static Glib::RefPtr<Application> create(int& argc,
                                          char**& argv,
                                          const Glib::ustring& application_id=Glib::ustring(),
                                          Gio::ApplicationFlags flags=Gio::APPLICATION_FLAGS_NONE);

  virtual ~Application();

protected:
  Application(int& argc,
              char**& argv,
              const Glib::ustring& application_id=Glib::ustring(),
              Gio::ApplicationFlags flags=Gio::APPLICATION_FLAGS_NONE);

  void on_startup() override;
  void on_activate() override;
  void on_open(const Gio::Application::type_vec_files& files,
	       const Glib::ustring& hint) override;
  void on_quit();

  void on_window_hide(MainWindow* window_);

private:
  MainWindow* window;
};

#endif
