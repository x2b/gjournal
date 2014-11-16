#ifndef PAGELAYOUT_HH
#define PAGELAYOUT_HH

#include <tuple>

#include <glibmm/property.h>

#include <gtkmm/layout.h>

class PageLayout : public Gtk::Layout
{
public:
  PageLayout();

  Glib::PropertyProxy<int> property_row_spacing()
  {
    return prop_row_spacing.get_proxy();
  }

  Glib::PropertyProxy<int> property_col_spacing()
  {
    return prop_row_spacing.get_proxy();
  }

  Glib::PropertyProxy<bool> property_dual()
  {
    return prop_dual.get_proxy();
  }

  Glib::PropertyProxy<bool> property_odd_left()
  {
    return prop_odd_left.get_proxy();
  }

protected:

  typedef std::tuple<Gtk::Widget*, Gtk::Widget*> LayoutRow;
  typedef std::tuple<const Gtk::Widget*, const Gtk::Widget*> ConstLayoutRow;

  enum class Alignment {LEFT, CENTER, RIGHT};

  std::vector<LayoutRow> get_layout_rows();
  std::vector<ConstLayoutRow> get_layout_rows() const;

  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;

  void get_preferred_width_dual(int& minimum_width, int& natural_width) const;

  void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;

  void get_preferred_height_dual(int& minimum_height, int& natural_height) const;

  void on_size_allocate(Gtk::Allocation& allocation) override;

  void size_allocate_dual(Gtk::Allocation& allocation);

  int place_child(Gtk::Widget& widget,
                  Alignment alignment,
                  int y, int width,
                  int additional_height);

  Glib::Property<int> prop_row_spacing, prop_col_spacing;

  Glib::Property<bool> prop_dual, prop_odd_left;
};

#endif
