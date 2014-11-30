#include "Color.hh"

#include <unordered_map>
#include <utility>
#include <stdexcept>

#include "util/Log.hh"
#include "util/ReadError.hh"

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

Color Color::create(Glib::ustring name)
{
  const std::unordered_map<std::string, Color>
    known_colors({{"black",	 Color(0x000000)},
		  {"blue",	 Color(0x3333cc)},
		  {"red",	 Color(0xff0000)},
		  {"green",	 Color(0x008000)},
		  {"gray",	 Color(0x808080)},
		  {"lightblue",	 Color(0x00c0ff)},
		  {"lightgreen", Color(0x00ff00)},
		  {"magenta",	 Color(0xff00ff)},
		  {"orange",	 Color(0xff8000)},
		  {"yellow",	 Color(0xffff00)},
		  {"white",	 Color(0xffffff)}});

  auto it = known_colors.find(name);

  if(it != known_colors.end())
  {
    return it->second;
  }

  ParseError(name).raise();

  return Color();
}

Color Color::parse(Glib::ustring str)
{
  Color col;
  
  if((str.size() == 9 or
      str.size() == 7) and
     str[0] == '#')
  {
    if(str[0] == '#')
    {
      col.r = std::stoi(str.substr(1, 2), 0, 16);
      col.g = std::stoi(str.substr(3, 2), 0, 16);
      col.b = std::stoi(str.substr(5, 2), 0, 16);

      if(str.size() == 9)
	col.a = std::stoi(str.substr(7, 2), 0, 16);
	
      return col;
    }
  }
  
  ParseError(str).raise();
  return col;
}
