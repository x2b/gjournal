#include "Document.hh"

#include "util/Error.hh"

void Document::append_page(PageRef page)
{
  int number = pages.size();

  page->set_number(number);

  pages.insert(std::make_pair(number, page));
}

void Document::remove_page(PageRef page)
{
  auto it = pages.begin();
  int i = 1;
  bool seen = false;

  gj_assert(page);

  for(;it != pages.end(); ++i, ++it)
  {
    if(page == it->second)
    {
      it = pages.erase(it);
      seen = true;
    }
    else if(seen)
    {
      it->second->set_number(i);
    }
  }

};

PageRef Document::find(int number)
{
  auto it = pages.find(number);

  if(it != pages.end())
    return it->second;

  return PageRef();
}


PageList Document::get_pages()
{
  return pages | boost::adaptors::map_values;
};

DocumentRef Document::create()
{
  return DocumentRef(new Document());
}

Document::Document()
{

}
