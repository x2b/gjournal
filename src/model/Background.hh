#ifndef BACKGROUND_HH
#define BACKGROUND_HH

#include <glibmm/object.h>

#include <cairomm/cairomm.h>

#include <gdkmm/pixbuf.h>

#include "Color.hh"

class Page;

/**
 * @brief Each Page of a Document comes with a Background
 *
 * The Background is either solid with a fixe
 * Background::BackgroundStyle or given by an image.
 */
class Background : public Glib::Object
{
public:
  Background(Page& page);

  /**
   * The type of this Background
   */
  enum BackgroundType
  {
    SOLID,
    ///< A solid background
    IMAGE
    ///< A background image
    //TODO: implement PDF
  };


  /**
   * The style of this Background. Only used
   * for a solid Background::BackgroundType
   */
  enum BackgroundStyle
  {
    NONE,
    ///< A plain background
    LINED,
    ///< A lined paper
    RULED,
    ///< Almost a lined paper
    GRAPH
    ///< A graph paper
  };

  void draw(const Cairo::RefPtr<Cairo::Context>& cr) const;

  /**
   * Sets this Page%'s background color
   */
  void set_color(Color background_color);

  /**
   * Sets this Page%'s background type
   */
  void set_type(BackgroundType background_type);

  void set_style(BackgroundStyle background_style);

  Glib::RefPtr<Gdk::Pixbuf> get_image();

  void set_image(Glib::RefPtr<Gdk::Pixbuf> image);

private:
  void draw_missing_background(const Cairo::RefPtr<Cairo::Context>& cr) const;

  void draw_background_ruled(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void draw_background_lined(const Cairo::RefPtr<Cairo::Context>& cr) const;
  void draw_background_graph(const Cairo::RefPtr<Cairo::Context>& cr) const;

  BackgroundType background_type;
  BackgroundStyle background_style;
  Color background_color;
  Page &page;
  Glib::RefPtr<Gdk::Pixbuf> background_image;

};


#endif /* BACKGROUND_HH */
