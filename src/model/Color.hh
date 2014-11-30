#ifndef COLOR_HH
#define COLOR_HH

#include <stdexcept>

#include <glibmm/ustring.h>
#include <cairomm/cairomm.h>

typedef unsigned char uchar;

class Color
{
public:
  Color();
  Color(int c);
  Color(uchar r, uchar g, uchar b, uchar a=0xff);

  void apply(const Cairo::RefPtr<Cairo::Context>& cr) const;

  static Color create(Glib::ustring name);
  static Color parse(Glib::ustring hex);

public:
  uchar r, g, b, a;
};

#endif
