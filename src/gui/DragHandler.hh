#ifndef DRAGHANDLER_HH
#define DRAGHANDLER_HH

#include <gtkmm/applicationwindow.h>

class MainWindow;

class DragHandler
{
public:
  DragHandler(MainWindow& parent_);

  void on_drop_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
			     int x, int y,
			     const Gtk::SelectionData& selection_data,
			     guint info, guint time);
  
private:
  MainWindow& parent;
};



#endif /* DRAGHANDLER_HH */
