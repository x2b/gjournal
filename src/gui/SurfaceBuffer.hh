#ifndef SURFACEBUFFER_HH
#define SURFACEBUFFER_HH

#include <cairomm/surface.h>

#include "model/Page.hh"

class SurfaceBuffer
{
public:
  SurfaceBuffer(PageRef page);

  void draw(const Cairo::RefPtr<Cairo::Context>& cr,
            int width, int height);

  virtual ~SurfaceBuffer();

private:
  void redraw(int width, int height);

  Cairo::RefPtr<Cairo::ImageSurface> surface;
  PageRef page;
};


#endif /* SURFACEBUFFER_HH */
