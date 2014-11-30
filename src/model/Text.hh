#ifndef TEXT_HH
#define TEXT_HH

#include <memory>

#include <pangomm/fontdescription.h>

#include "Color.hh"
#include "Element.hh"
#include "Point.hh"

class Text;

typedef std::shared_ptr<Text> TextRef;

class Text : public Element
{
public:
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr) const override;
  virtual Rectangle bounding_rect() const override;

  virtual void move(Point& offset) override;
  virtual void scale(Point& src, double dx, double dy) override;

  virtual ~Text();

  void set_color(Color c);

  static TextRef create(const Glib::ustring& text_,
                        const Glib::ustring& font_desc,
                        const double& font_size,
                        const Point& point_);

private:
  Text(const Glib::ustring& text_,
       const Glib::ustring& font_desc,
       const double& font_size,
       const Point& point_);

  Glib::ustring text;
  Point point;
  Pango::FontDescription font;
  Color color;
};

#endif /* TEXT_HH */
