#ifndef LAMBDA_HH
#define LAMBDA_HH

// unfortunately sigc++ needs some help to be
// able to deal with lambdas...

// See https://stackoverflow.com
//     /questions/13805883
//     /use-lambda-in-connection-with-sigc-library

#include <type_traits>
#include <sigc++/sigc++.h>
namespace sigc
{   
  template <typename Functor>
  struct functor_trait<Functor, false>
  {   
    typedef decltype (::sigc::mem_fun (std::declval<Functor&> (), 
                                       &Functor::operator())) _intermediate;

    typedef typename _intermediate::result_type result_type;
    typedef Functor functor_type;
  };  
}   

#endif /* LAMBDA_HH */
