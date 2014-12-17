#include "Image.hh"

#include "util/Lambda.hh"
#include "util/Log.hh"

Image::Image(Rectangle position_, const std::string& data_str)
  : position(position_)
{
  TRACE;

  unsigned int str_len = data_str.size(),
    read_pos = 0;

  auto func = [&] (unsigned char* data, unsigned int length)
    -> Cairo::ErrorStatus
  {
    for (unsigned int i = 0; i < length; ++i, ++read_pos)
    {
      if(read_pos >= str_len)
      {
        return CAIRO_STATUS_READ_ERROR;
      }
      data[i] = data_str[read_pos];
    }

    
    return CAIRO_STATUS_SUCCESS;
  };
  
  surface = Cairo::ImageSurface::create_from_png_stream(func);
}


void Image::draw(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  double x_factor = position.get_width() / double(surface->get_width()),
    y_factor = position.get_height() / double(surface->get_height());

  cr->scale(x_factor, y_factor);
  cr->set_operator(Cairo::OPERATOR_OVER);
  cr->set_source(surface,
                 position.get_x() / x_factor,
                 position.get_y() / y_factor);
  cr->paint();
}

Rectangle Image::bounding_rect() const
{
  return position;
}

void Image::move(Point& offset)
{
  
}

void Image::scale(Point& src, double dx, double dy)
{
}


ImageRef Image::create(Rectangle position,
                       const std::string& data)
{
  return ImageRef(new Image(position, data));
}
