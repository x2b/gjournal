#ifndef ZOOMLEVEL_HH
#define ZOOMLEVEL_HH


struct ZoomLevel
{
  ZoomLevel(std::string name_, double level_)
    : name(name_), level(level_)
  {}

  std::string name;
  double level;
};


const std::vector<ZoomLevel> levels({ZoomLevel("50%", 0.5),
                                     ZoomLevel("70%", 0.7071067811),
                                     ZoomLevel("85%", 0.8408964152),
                                     ZoomLevel("100%", 1.0),
                                     ZoomLevel("125%", 1.1892071149),
                                     ZoomLevel("150%", 1.4142135623),
                                     ZoomLevel("175%", 1.6817928304),
                                     ZoomLevel("200%", 2.0),
                                     ZoomLevel("400%", 4.0)});

const double max_zoom = 4.0f;
const double min_zoom = 0.5f;
const double zoom_inc = 1.05f;

// margins are used for scroll to page / fit to page
const int page_margin = 15;

#endif /* ZOOMLEVEL_HH */
