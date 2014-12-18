#ifndef IMAGE_HH
#define IMAGE_HH

#include "Element.hh"

class Image;

typedef std::shared_ptr<Image> ImageRef;

class Image : public Element
{
private:
  Image(Rectangle position, const std::string& data);

public:
  virtual void draw(const Cairo::RefPtr<Cairo::Context>& cr)
    const override;

  virtual Rectangle bounding_rect() const override;

  virtual void move(Point& offset) override;
  virtual void scale(Point& src, double dx, double dy) override;

  static ImageRef create(Rectangle position,
                         const std::string& data);

private:
  Rectangle position;
  Cairo::RefPtr<Cairo::ImageSurface> surface;
};


#endif /* IMAGE_HH */
