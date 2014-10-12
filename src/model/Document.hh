#ifndef DOCUMENT_HH
#define DOCUMENT_HH

#include <list>

#include "Page.hh"

typedef std::list<PageRef> PageList;

class Document
{
public:

  template<typename... Args>
  PageRef appendPage(Args&&... args)
  {
    PageRef page = std::make_shared<Page>(std::forward<Args>(args)...);
    page->setNumber(pages.size());
    pages.push_back(page);
    return page;
  }
  
  void removePage(PageRef page);
  
  PageList& getPages();
  
private:
  PageList pages;
};

#endif
