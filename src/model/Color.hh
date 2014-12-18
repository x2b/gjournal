#ifndef COLOR_HH
#define COLOR_HH

#include <stdexcept>

#include <glibmm/ustring.h>
#include <cairomm/cairomm.h>

typedef unsigned char uchar;

/**
 * @brief An RGBA color
 */
class Color
{
public:
  Color();
  Color(int c);
  Color(uchar r, uchar g, uchar b, uchar a=0xff);

  /**
   * Sets the source RGBA of the given Cairo::Context
   */
  void apply(const Cairo::RefPtr<Cairo::Context>& cr) const;

  /**
   * Creates a Color from a well-known name
   */
  static Color create(Glib::ustring name);

  /**
   * Creates a Color from a hexadecimal string
   */
  static Color parse(Glib::ustring hex);

public:
  uchar r, ///< The red   component.
    g,     ///< The green component.
    b,     ///< The blue  component.
    a;     ///< The alpha component.
};

#endif
