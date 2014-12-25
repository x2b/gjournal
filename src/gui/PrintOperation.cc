#include "PrintOperation.hh"

#include "util/Error.hh"
#include "util/Log.hh"

PrintOperation::PrintOperation(DocumentRef doc_)
  : doc(doc_)
{
  gj_assert(doc);
  set_use_full_page(true);
}

Glib::RefPtr<PrintOperation>
PrintOperation::create(DocumentRef doc)
{
  return Glib::RefPtr<PrintOperation>(new PrintOperation(doc));
}

void PrintOperation::on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context)
{
  TRACE;

  set_n_pages(doc->count_pages());
}

void PrintOperation::on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context,
                                  int page_no)
{
  TRACE;

  LOG(DEBUG) << "Page number: " << page_no;

  Cairo::RefPtr<Cairo::Context> cr = context->get_cairo_context();

  const double cr_width = context->get_width(),
    cr_height = context->get_height();

  PageRef current_page = doc->find(page_no);

  if(not(current_page))
    return;

  cr->scale(cr_width / current_page->get_width(),
            cr_height / current_page->get_height());

  current_page->draw(cr);
}
PrintOperation::~PrintOperation()
{

}


