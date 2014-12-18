#ifndef XOJREADER_HH
#define XOJREADER_HH

#include <libxml++/parsers/domparser.h>

#include "model/Document.hh"

/**
 * @brief Reads a Document from XML files
 */
class XojReader
{
public:
  XojReader();
  virtual ~XojReader();

  /**
   * Reads a Document
   *
   * @param filename The name of the file to be used.
   */
  DocumentRef read_from_file(const Glib::ustring& filename);

private:
  ElementRef parse_element(const xmlpp::Node* node);
  LayerRef parse_layer(const xmlpp::Node* node);
  PageRef parse_page(const xmlpp::Node* node);

  Color parse_color(Glib::ustring& color_name);

  void parse_background(const xmlpp::Node* node,
                        PageRef page);

  std::vector<double> parse_list(Glib::ustring str);
};

#endif /* XOJREADER_HH */
