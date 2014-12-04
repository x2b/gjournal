#ifndef PRINTOPERATION_HH
#define PRINTOPERATION_HH

#include <gtkmm/printoperation.h>

#include  "model/Document.hh"

class PrintOperation : public Gtk::PrintOperation
{
public:
  virtual ~PrintOperation();

  static Glib::RefPtr<PrintOperation> create(DocumentRef doc);

protected:
  void on_begin_print(const Glib::RefPtr<Gtk::PrintContext>& context) override;

  void on_draw_page(const Glib::RefPtr<Gtk::PrintContext>& context,
                    int page_no) override;

  PrintOperation(DocumentRef doc);

  DocumentRef doc;
};


#endif /* PRINTOPERATION_HH */
