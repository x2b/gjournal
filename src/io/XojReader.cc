#include "XojReader.hh"

#include <string>
#include <unordered_map>

#include <glibmm/base64.h>
#include <glibmm/convert.h>

#include "model/Color.hh"
#include "model/Image.hh"
#include "model/Pen.hh"
#include "model/PressureStroke.hh"
#include "model/Stroke.hh"
#include "model/Text.hh"

#include "util/Log.hh"
#include "util/ReadError.hh"

XojReader::XojReader()
{

}

DocumentRef XojReader::read_from_file(const Glib::ustring& filename)
{
  DocumentRef doc = Document::create();

  doc->set_uri(filename);


  LOG(INFO) << "Reading file \"" << filename << "\"";

  xmlpp::DomParser parser;

  //TODO: error handling
  parser.parse_file(filename);

  xmlpp::Element* root = parser.get_document()->get_root_node();

  for(const xmlpp::Node* page_node : root->find("/xournal/page"))
  {
    doc->append_page(parse_page(page_node));
  }

  LOG(INFO) << "Read in a document with "
	    << doc->count_pages() << " pages";

  return doc;
}

PageRef XojReader::parse_page(const xmlpp::Node* node)
{
  PageRef page;
  const xmlpp::Element* element =
    dynamic_cast<const xmlpp::Element*>(node);

  Glib::ustring width_name = element->get_attribute_value("width"),
    height_name = element->get_attribute_value("height");

  double width = std::stod(width_name),
    height = std::stod(height_name);

  LOG(DEBUG) << "Reading a page of dimensions "
	     << width << "x" << height;

  page = Page::create(width, height);

  parse_background(node, page);

  for(const xmlpp::Node* layer_node : node->find("layer"))
  {
    page->add_layer(parse_layer(layer_node));
  }


  return page;
}

void XojReader::parse_background(const xmlpp::Node* page_node,
				 PageRef page)
{
  const xmlpp::Node* background_node =
    page_node->get_first_child("background");

  const xmlpp::Element* background_element =
    dynamic_cast<const xmlpp::Element*>(background_node);

  if(not(background_element))
    return;

  Glib::ustring
    style_name = background_element->get_attribute_value("style"),
    color_name = background_element->get_attribute_value("color");

  page->set_background_color(parse_color(color_name));

  const std::unordered_map<std::string, Page::BackgroundType>
    known_bg_types({{"plain", Page::BackgroundType::NONE},
	{"lined", Page::BackgroundType::LINED},
	{"ruled", Page::BackgroundType::RULED},
	{"graph", Page::BackgroundType::GRAPH},});

  auto it = known_bg_types.find(style_name);

  if(it != known_bg_types.end())
  {
    page->set_background_type(it->second);
  }
  else
  {
    page->set_background_type(Page::BackgroundType::NONE);
    LOG(ERROR) << "Could not find background type "
	       << style_name;
  }

}

ElementRef XojReader::parse_element(const xmlpp::Node* node)
{
  Glib::ustring name = node->get_name();
  const xmlpp::Element* element =
    dynamic_cast<const xmlpp::Element*>(node);

  if(name == "stroke")
  {
    Glib::ustring tool_name = element->get_attribute_value("tool"),
      color_name = element->get_attribute_value("color"),
      width_name = element->get_attribute_value("width");

    // tool_name: pen / eraser / highlighter

    Color color = parse_color(color_name);

    if(tool_name == "pen")
    {

    }
    else if(tool_name == "eraser")
    {

    }
    else if(tool_name == "highlighter")
    {
      color.a = 120u;
    }

    const xmlpp::TextNode* point_element =
      element->get_child_text();

    std::vector<double> width_vector(parse_list(width_name)),
      point_vector(parse_list(point_element->get_content()));

    //LOG(DEBUG) << point_element->get_content();

    if(width_vector.size() == 1)
    {
      Pen pen;
      pen.set_width(*width_vector.begin());
      pen.set_color(color);

      StrokeRef stroke = Stroke::create(pen);

      auto it = point_vector.begin();

      while(it != point_vector.end())
      {
	double x = *it;
	++it;
	double y = *it;
	++it;

	stroke->get_points().push_back(Point(x, y));
      }

      return stroke;
    }
    else
    {
      Pen pen;
      pen.set_width(*width_vector.begin());
      pen.set_color(color);

      PressureStrokeRef stroke = PressureStroke::create(pen);

      auto it = point_vector.begin(),
	vit = width_vector.begin();

      while(it != point_vector.end())
      {
	double x = *it;
	++it;
	double y = *it;
	++it;
	double z = *vit;
	++vit;

	stroke->get_points().push_back(PressurePoint(x, y, z));
      }

      return stroke;
    }
  }
  else if(name == "text" and element)
  {
    Glib::ustring font_name = element->get_attribute_value("font"),
      size_name = element->get_attribute_value("size"),
      x_name = element->get_attribute_value("x"),
      y_name = element->get_attribute_value("y"),
      color_name = element->get_attribute_value("color");

    Glib::ustring text_content =
      element->get_child_text()->get_content();

    Point point(std::stod(x_name), std::stod(y_name));

    auto text = Text::create(text_content, font_name,
			     std::stod(size_name), point);

    text->set_color(parse_color(color_name));

    return text;
  }
  else if(name == "image")
  {
    Glib::ustring top_name = element->get_attribute_value("top"),
      bottom_name = element->get_attribute_value("bottom"),
      left_name = element->get_attribute_value("left"),
      right_name = element->get_attribute_value("right");

    double top = std::stod(top_name),
      bottom = std::stod(bottom_name),
      left = std::stod(left_name),
      right = std::stod(right_name);

    Rectangle position(left, top, right - left, bottom - top);

    const xmlpp::TextNode* data_element =
      element->get_child_text();

    std::string data
      = Glib::Base64::decode(data_element->get_content());

    return Image::create(position, data);
  }

  return nullptr;
}

Color XojReader::parse_color(Glib::ustring& color_name)
{
  if(not(color_name.empty()))
  {
    if(color_name[0] == '#')
    {
      return Color::parse(color_name);
    }
    else
    {
      return Color::create(color_name);
    }
  }

  ParseError(color_name).raise();

  return Color();
}

LayerRef XojReader::parse_layer(const xmlpp::Node* layer_node)
{
  LayerRef layer(Layer::create());

  for(const xmlpp::Node* element_node : layer_node->get_children())
  {
    layer->add_element(parse_element(element_node));
  }

  return layer;
}

std::vector<double> XojReader::parse_list(Glib::ustring str)
{
  std::vector<double> values;
  std::istringstream is(str);

  double val;

  while(is >> val)
    values.push_back(val);

  return values;
}

XojReader::~XojReader()
{
}
