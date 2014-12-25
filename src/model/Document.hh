#ifndef DOCUMENT_HH
#define DOCUMENT_HH

#include <memory>
#include <unordered_map>

#include <boost/range/adaptor/map.hpp>

#include <glibmm/ustring.h>

#include "Page.hh"

class Document;

typedef std::shared_ptr<Document> DocumentRef;

/**
 * @brief A Document is a collection of Pages%s
 */
class Document
{
public:

  template<typename... Args>
  PageRef append_page(Args&&... args)
  {
    PageRef page = Page::create(std::forward<Args>(args)...);
    append_page(page);
    return page;
  }

  /**
   * Appends a Page to this Document
   */
  void append_page(PageRef page);

  /**
   * Removes the specified Page from this Document.
   */
  void remove_page(PageRef page);

  /**
   * Returns the number of Page%s in this Document.
   */
  int count_pages() const
  {
    return pages.size();
  }

  /**
   * Returns whether this Document is empty.
   */
  bool empty() const
  {
    return pages.empty();
  }

  /**
   * Returns this Docuemnt%'s URI.
   */
  Glib::ustring get_uri()
  {
    return uri;
  }

  /**
   * Sets this Docuemnt%'s URI.
   */
  void set_uri(const Glib::ustring& name)
  {
    uri = name;
  }

  std::unordered_map<int, PageRef> pages;

  /**
   * Creates a new Document.
   */
  static DocumentRef create();

  typedef decltype(pages
                   | boost::adaptors::map_values) PageList;

  /**
   * Returns a list of Page%s.
   */
  PageList get_pages();

  PageRef find(int number);

private:
  Document();

  Glib::ustring uri;
};

typedef Document::PageList PageList;

#endif
