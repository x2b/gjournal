#ifndef APPLICATION_HH
#define APPLICATION_HH

#include <gtkmm/application.h>

class MainWindow;

class Application : public Gtk::Application
{
public:
  static Glib::RefPtr<Application> create();

  virtual ~Application();

protected:
  Application();

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
