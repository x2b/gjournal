#include "SurfaceBuffer.hh"

#include "util/Log.hh"

SurfaceBuffer::SurfaceBuffer(PageRef page_)
  : page(page_)
{

}

void SurfaceBuffer::draw(const Cairo::RefPtr<Cairo::Context>& cr,
                         int width, int height)
{
  TRACE;

  if(not(surface) or
     surface->get_width() != width or
     surface->get_height() != height)
  {
    redraw(width, height);
  }

  cr->set_source(surface, 0, 0);
  cr->paint();
}

void SurfaceBuffer::redraw(int width, int height)
{
  TRACE;

  surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32,
                                        width, height);

  double factor_x = double(width) / page->get_width(),
    factor_y = double(height) / page->get_height();

  auto cr = Cairo::Context::create(surface);

  cr->scale(factor_x, factor_y);

  page->draw(cr);
}

SurfaceBuffer::~SurfaceBuffer()
{

}
