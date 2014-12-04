#include "DragHandler.hh"

#include "MainWindow.hh"
#include "util/Log.hh"

DragHandler::DragHandler(MainWindow& parent_)
  : parent(parent_)
{
  using namespace std::placeholders;

  std::vector<Gtk::TargetEntry> list_targets;
  list_targets.push_back(Gtk::TargetEntry("text/uri-list"));

  parent.drag_dest_set(list_targets);

  auto func =
    std::bind(&DragHandler::on_drop_data_received, this,
	      _1, _2, _3, _4, _5, _6);

  parent.signal_drag_data_received().connect(func);
}


void DragHandler::on_drop_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
                                        int x, int y,
                                        const Gtk::SelectionData& selection_data,
                                        guint info, guint time)
{
  TRACE;

  for(auto target : context->list_targets())
  {
    if(target == "text/uri-list")
    {
      for(const std::string& uri : selection_data.get_uris())
      {
	LOG(DEBUG) << "URI: " << uri;
	parent.read_document(Gio::File::create_for_uri(uri));
      }
    }
  }
}
