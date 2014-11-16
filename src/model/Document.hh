#ifndef DOCUMENT_HH
#define DOCUMENT_HH

#include <list>
#include <memory>
#include <string>

#include "Page.hh"

typedef std::list<PageRef> PageList;

class Document;

typedef std::shared_ptr<Document> DocumentRef;

class Document
{
public:

  template<typename... Args>
  PageRef appendPage(Args&&... args)
  {
    PageRef page = std::make_shared<Page>(std::forward<Args>(args)...);
    page->set_number(pages.size());
    pages.push_back(page);
    return page;
  }

  void remove_page(PageRef page);

  PageList& get_pages();

  std::string& get_URI()
  {
    return uri;
  }

  static DocumentRef create();

private:
  Document();
  PageList pages;

  std::string uri;
};

#endif
