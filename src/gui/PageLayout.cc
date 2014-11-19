#include "PageLayout.hh"

#include "util/Log.hh"

PageLayout::PageLayout()
  : Glib::ObjectBase(typeid(PageLayout)),
    prop_row_spacing(*this, "row-spacing", 10),
    prop_col_spacing(*this, "col-spacing", 50),
    prop_dual(*this, "dual", false),
    prop_odd_left(*this, "odd-left", true)
{
  auto layout = std::bind(&PageLayout::queue_resize, this);

  property_row_spacing().signal_changed().connect(layout);
  property_col_spacing().signal_changed().connect(layout);
  property_dual().signal_changed().connect(layout);
  property_odd_left().signal_changed().connect(layout);
}

std::vector<PageLayout::LayoutRow> PageLayout::get_layout_rows()
{
  std::vector<PageLayout::LayoutRow> rows;
  std::vector<Gtk::Widget*> children = get_children();

  auto it = children.begin(), end = children.end();

  bool first_page = true;

  while(it != end)
  {
    Gtk::Widget *first_child = *it,
                *second_child = nullptr;

    if(first_page and !prop_odd_left.get_value())
    {
      first_page = false;

      second_child = first_child;
      first_child = nullptr;
    }
    else if(++it != end)
      second_child = *it;

    if(first_child and not(first_child->get_visible()))
      first_child = nullptr;

    if(second_child and not(second_child->get_visible()))
      second_child = nullptr;

    if(first_child or second_child)
      rows.push_back(std::make_tuple(first_child, second_child));

    if(it == end)
      break;
    else
      ++it;
  }

  return rows;
}


std::vector<PageLayout::ConstLayoutRow> PageLayout::get_layout_rows() const
{
  std::vector<PageLayout::ConstLayoutRow> rows;
  std::vector<const Gtk::Widget*> children = get_children();

  auto it = children.begin(), end = children.end();

  bool first_page = true;

  while(it != end)
  {
    const Gtk::Widget *first_child = *it,
                      *second_child = nullptr;

    if(first_page and !prop_odd_left.get_value())
    {
      first_page = false;

      second_child = first_child;
      first_child = nullptr;
    }
    else if(++it != end)
      second_child = *it;

    if(first_child and not(first_child->get_visible()))
      first_child = nullptr;

    if(second_child and not(second_child->get_visible()))
      second_child = nullptr;

    if(first_child or second_child)
      rows.push_back(std::make_tuple(first_child, second_child));

    if(it == end)
      break;
    else
      ++it;
  }

  return rows;
}

bool PageLayout::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation alloc = get_allocation();

  bool x = Gtk::Layout::on_draw(cr);

  /*
  cr->set_source_rgba(0, 0.8, 0, 1);
  cr->move_to(0, 0);
  cr->line_to(alloc.get_width(), alloc.get_height());
  cr->move_to(alloc.get_width(), 0);
  cr->line_to(0, alloc.get_height());
  cr->stroke();
  */

  return x;
}

void PageLayout::get_preferred_width_vfunc(int& minimum_width, int& natural_width) const
{
  minimum_width = natural_width = 0;

  if(prop_dual.get_value())
  {
    return get_preferred_width_dual(minimum_width, natural_width);
  }

  int margin = get_margin_left() + get_margin_right();

  for(const Gtk::Widget* widget : get_children())
  {
    int widget_minimum_width, widget_natural_width;

    if(!widget->get_visible())
      continue;

    widget->get_preferred_width(widget_minimum_width, widget_natural_width);

    minimum_width = std::max(minimum_width, widget_minimum_width);
    natural_width = std::max(natural_width, widget_natural_width);
  }

  minimum_width += margin;
  natural_width += margin;

  LOG(DEBUG) << "PageLayout::get_preferred_width_vfunc returns " << minimum_width;
}

void PageLayout::get_preferred_height_vfunc(int& minimum_height, int& natural_height) const
{
  minimum_height = natural_height = 0;
  int n_visible = 0;

  if(prop_dual.get_value())
  {
    return get_preferred_height_dual(minimum_height, natural_height);
  }

  for(const Gtk::Widget* widget : get_children())
  {
    if(!widget->get_visible())
      continue;

    ++n_visible;

    int widget_minimum_height, widget_natural_height;

    widget->get_preferred_height(widget_minimum_height, widget_natural_height);

    minimum_height += widget_minimum_height;
    natural_height += widget_natural_height;
  }

  int margin = get_margin_top() + get_margin_bottom();

  if(n_visible > 1)
  {
    margin += (n_visible - 1) * prop_row_spacing.get_value();
  }

  minimum_height += margin;
  natural_height += margin;

  LOG(DEBUG) << "PageLayout::get_preferred_height_vfunc returns "
             << minimum_height
             << " for a total of children: "
             << get_children().size();
}

void PageLayout::get_preferred_height_dual(int& minimum_height, int& natural_height) const
{
  minimum_height = natural_height = 0;
  int n_visible = 0;

  for(auto& row : get_layout_rows())
  {
    const Gtk::Widget *first_child = nullptr,
                      *second_child = nullptr;

    std::tie(first_child, second_child) = row;

    int first_minimum_height = 0,
        first_natural_height = 0,
        second_minimum_height = 0,
        second_natural_height = 0;

    if(first_child)
    {
      first_child->get_preferred_height(first_minimum_height,
                                        first_natural_height);
    }

    if(second_child)
    {
      second_child->get_preferred_height(second_minimum_height,
                                         second_natural_height);
    }

    minimum_height += std::max(first_minimum_height,
                               second_minimum_height);

    natural_height += std::max(first_natural_height,
                               second_natural_height);

    if(first_child or second_child)
    {
      ++n_visible;
    }
  }

  int margin = get_margin_top() + get_margin_bottom();

  if(n_visible > 1)
  {
    margin += (n_visible - 1) * prop_row_spacing.get_value();
  }

  minimum_height += margin;
  natural_height += margin;
}

void PageLayout::get_preferred_width_dual(int& minimum_width, int& natural_width) const
{
  minimum_width = natural_width = 0;

  for(auto& row : get_layout_rows())
  {
    const Gtk::Widget *first_child = nullptr,
                      *second_child = nullptr;

    std::tie(first_child, second_child) = row;

    int first_minimum_width = 0,
        first_natural_width = 0,
        second_minimum_width = 0,
        second_natural_width = 0;

    if(first_child)
    {
      first_child->get_preferred_width(first_minimum_width,
                                       first_natural_width);
    }

    if(second_child)
    {
      second_child->get_preferred_width(second_minimum_width,
                                        second_natural_width);

      first_minimum_width += second_minimum_width;
      first_natural_width += second_natural_width;
    }

    if(first_child and second_child)
    {
       first_minimum_width += prop_col_spacing.get_value();
       first_natural_width += prop_col_spacing.get_value();
    }

    minimum_width = std::max(minimum_width, first_minimum_width);
    natural_width = std::max(natural_width, first_natural_width);
  }

  int margin = get_margin_left() + get_margin_right();

  minimum_width += margin;
  natural_width += margin;
}

void PageLayout::on_size_allocate(Gtk::Allocation& allocation)
{
  set_allocation(allocation);

  if(get_realized() and get_has_window())
  {
    get_window()->move_resize(allocation.get_x(),
                              allocation.get_y(),
                              allocation.get_width(),
                              allocation.get_height());
  }

  set_size(allocation.get_width(), allocation.get_height());

  if(prop_dual.get_value())
  {
    return size_allocate_dual(allocation);
  }

  //int x = allocation.get_x() - get_margin_left();
  int y = allocation.get_y() - get_margin_top();

  int n_expanding = 0,
      n_visible = 0,
      min_height = 0;

  auto children = get_children();

  for(Gtk::Widget* widget : children)
  {
    if(!widget->get_visible())
      continue;

    ++n_visible;

    int widget_minimum_height, widget_natural_height;

    widget->get_preferred_height(widget_minimum_height, widget_natural_height);

    min_height += widget_minimum_height;

    if(widget->get_vexpand())
      ++n_expanding;
  }

  int expanding_height = 0;

  if(n_expanding > 0)
  {
    expanding_height = (allocation.get_height() - min_height);

    if(n_visible > 1)
      expanding_height -= (n_visible - 1) * prop_row_spacing.get_value();

    expanding_height /= (n_expanding);
  }

  for(Gtk::Widget* widget : children)
  {
    if(!widget->get_visible())
      continue;

    y = place_child(*widget, Alignment::CENTER,
                    y, allocation.get_width(),
                    expanding_height);

    y += prop_row_spacing.get_value();
  }
}

void PageLayout::size_allocate_dual(Gtk::Allocation& allocation)
{
  auto rows = get_layout_rows();

  int n_visible = 0,
      n_expanding = 0;

  int min_height = 0;

  for(auto& row : get_layout_rows())
  {
    const Gtk::Widget *first_child = nullptr,
                      *second_child = nullptr;

    std::tie(first_child, second_child) = row;

    ++n_visible;

    int first_minimum_height = 0,
        first_natural_height = 0,
        second_minimum_height = 0,
        second_natural_height = 0;

    if(first_child)
    {
      first_child->get_preferred_height(first_minimum_height,
                                        first_natural_height);
    }

    if(second_child)
    {
      second_child->get_preferred_height(second_minimum_height,
                                         second_natural_height);
    }

    min_height += std::max(first_minimum_height, second_minimum_height);

    if((first_child and first_child->get_vexpand()) or
       (second_child and second_child->get_vexpand()))
      ++n_expanding;
  }

  int expanding_height = 0;

  if(n_expanding > 0)
  {
    expanding_height = (allocation.get_height() - min_height);

    if(n_visible > 1)
      expanding_height -= (n_visible - 1) * prop_row_spacing.get_value();

    expanding_height /= (n_expanding);
  }

  int y = allocation.get_y() - get_margin_top();

  for(auto& row : get_layout_rows())
  {
    Gtk::Widget *first_child = nullptr,
                *second_child = nullptr;

    std::tie(first_child, second_child) = row;

    int y1 = 0, y2 = 0;

    if(first_child)
    {
      y1 = place_child(*first_child, Alignment::LEFT,
                       y, allocation.get_width(),
                       expanding_height);
    }

    if(second_child)
    {
      y2 = place_child(*second_child, Alignment::RIGHT,
                       y, allocation.get_width(),
                       expanding_height);
    }

    y = std::max(y1, y2)  + prop_row_spacing.get_value();
  }
}

int PageLayout::place_child(Gtk::Widget& widget,
                            PageLayout::Alignment alignment,
                            int y, int width,
                            int additional_height)
{
  Gtk::Allocation alloc;

  int minimum_width, natural_width;

  alloc.set_y(y);

  widget.get_preferred_width(minimum_width, natural_width);

  if(alignment == Alignment::CENTER)
  {
    if(widget.get_vexpand())
    {
      alloc.set_x(0);
      alloc.set_width(width);
    }
    else
    {
      alloc.set_x((width - minimum_width) / 2);
      alloc.set_width(minimum_width);
    }
  }
  else if(alignment == Alignment::LEFT)
  {
    int r = (width - prop_col_spacing.get_value()) / 2;

    if(widget.get_vexpand())
    {
      alloc.set_x(0);
      alloc.set_width(r);
    }
    else
    {
      alloc.set_x(r - minimum_width);
      alloc.set_width(minimum_width);
    }
  }
  else if(alignment == Alignment::RIGHT)
  {
    int l = (width + prop_col_spacing.get_value()) / 2;

    alloc.set_x(l);

    if(widget.get_vexpand())
    {
      alloc.set_width(width - l);
    }
    else
    {
      alloc.set_width(minimum_width);
    }
  }

  int minimum_height, natural_height;

  widget.get_preferred_height(minimum_height, natural_height);

  if(widget.get_hexpand())
  {
    alloc.set_height(minimum_height + additional_height);
  }
  else
  {
    alloc.set_height(minimum_height);
  }

  widget.size_allocate(alloc);

  return y + alloc.get_height();
}
