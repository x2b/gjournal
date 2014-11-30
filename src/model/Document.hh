#ifndef DOCUMENT_HH
#define DOCUMENT_HH

#include <list>
#include <memory>

#include <glibmm/ustring.h>

#include "Page.hh"

typedef std::list<PageRef> PageList;

class Document;

typedef std::shared_ptr<Document> DocumentRef;

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

  void append_page(PageRef page);

  void remove_page(PageRef page);

  PageList& get_pages();

  int count_pages() const
  {
    return pages.size();
  }

  Glib::ustring get_uri()
  {
    return uri;
  }

  void set_uri(const Glib::ustring& name)
  {
    uri = name;
  }

  static DocumentRef create();

private:
  Document();
  PageList pages;

  Glib::ustring uri;
};

#endif
