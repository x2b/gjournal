#include "Color.hh"

Color::Color()
  : r(0xff), g(0xff),
    b(0xff), a(0xff)
{
}

Color::Color(int c)
  : r((c >> 16) & 0xff),
    g((c >> 8) & 0xff),
    b(c & 0xff),
    a(0xff)
{
  
}

Color::Color(uchar r, uchar g, uchar b, uchar a)
  : r(r), g(g), b(b), a(a)
{
}

void Color::apply(const Cairo::RefPtr<Cairo::Context>& cr) const
{
  cr->set_source_rgba(r/255., g/255., b/255., a/255.);
}
