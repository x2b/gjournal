#include "Document.hh"

void Document::append_page(PageRef page)
{
  page->set_number(pages.size());
  pages.push_back(page);
}

void Document::remove_page(PageRef page)
{
  auto it = get_pages().begin();
  int i = 1;
  bool seen = false;

  for(;it != get_pages().end(); ++i, ++it)
  {
    if(page == *it)
    {
      it = get_pages().erase(it);
      seen = true;
    }
    else if(seen)
    {
      (*it)->set_number(i);
    }
  }

};

PageList& Document::get_pages()
{
  return pages;
};

DocumentRef Document::create()
{
  Document* doc = new Document();
  return DocumentRef(doc);
}

Document::Document()
{

}
