#include "Document.hh"

void Document::removePage(PageRef page)
{
  auto it = getPages().begin();
  int i = 1;
  bool seen = false;
  
  for(;it != getPages().end(); ++i, ++it)
  {
    if(page == *it)
    {
      it = getPages().erase(it);
      seen = true;
    }
    else if(seen)
    {
      (*it)->setNumber(i);
    }
  }
  
};

PageList& Document::getPages()
{
  return pages;
};
