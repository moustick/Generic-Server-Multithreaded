//
// Functor.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/functors
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Mon Jan 28 14:44:18 2013 luca savarino
//

#ifndef FUNCTOR_1__
# define	FUNCTOR_1__

#include "Functor.hpp"

namespace functor
{
  template <class U, class V>
  class	Functor<U (V)>
  {
  public :

    typedef	typename type<U>::_t	(*expected)(typename type<V>::_t);

  private :
    class INestedFunctor
    {
    public :
      virtual			~INestedFunctor();

      virtual typename type<U>::_t	operator()(typename type<V>::_t)						    const = 0;
      bool				isCallable()	const = 0;
    };

    class Function : public INestedFunctor
    {
      expected		_function;

    public :
      Function(Function const&);
      Function(expected const&);
      ~Function();
      
      typename type<U>::_t		operator()(typename type<V>::_t)						    const;
      bool				isCallable()	const;
    };
    template <class Y>
    class Object : public INestedFunctor
    {
    public :
      typedef typename type<U>::_t		(Y::*expected2)(typename type<V>::_t);
    private :
      Y		const			*_object;
      expected2				_function;
    public :
      Object(Object const&);
      Object(Y const&, expected2 const& function = &Y::operator());
      ~Object();
      
      typename type<U>::_t		operator()(typename type<V>::_t)						    const;
      bool				isCallable()	const;
    };

    smartpointer::SharedPointerBase<INestedFunctor>		_functor;

  public :
    Functor();
    Functor(Functor<U (V)> const&);
    Functor(expected const&);
    template <class X>
    Functor(X & object, typename type<U>::_t  (X::*function)(typename type<V>::_t) = &X::operator());
    ~Functor();

    Functor<U (V)>		&			operator=(Functor<U (V)> const&);
    typename type<U>::_t				operator()(typename type<V>::_t)				 const;
    bool						isCallable()	const;
  };

  template <class U, class V>
  Functor<U (V)>::INestedFunctor::~INestedFunctor()
  {}

  template <class U, class V>
  Functor<U (V)>::Function::Function(Function const& to_copy)
    : _function(to_copy._function)
  {}
  
  template <class U, class V>
  Functor<U (V)>::Function::Function(expected const& function)
    : _function(function)
  {}

  template <class U, class V>
  Functor<U (V)>::Function::~Function()
  {}
  
  template <class U, class V>
  typename type<U>::_t		Functor<U (V)>::Function::operator()(typename type<V>::_t a)				    const
  {
    if (_function == NULL)
      throw "Trying to call a NULL function";
    return (_function(a));
  }

  template <class U, class V>
  bool		Functor<U (V)>::Function::isCallable()	const
  {
    return (_function != NULL);
  }

  template <class U, class V>
  template <class Y>
  Functor<U (V)>::Object<Y>::Object(Object const& to_copy)
    : _object(to_copy._object), _function(to_copy._function)
  {}
  
  template <class U, class V>
  template <class Y>
  Functor<U (V)>::Object<Y>::Object(Y const& object, expected2 const& function)
    : _object(&object), _function(function)
  {}
  
  template <class U, class V>
  template <class Y>
  Functor<U (V)>::Object<Y>::~Object()
  {}

  template <class U, class V>
  template <class Y>
  typename type<U>::_t			Functor<U (V)>::Object<Y>::operator()(typename type<V>::_t a)		const
  {
    if (_function == NULL)
      throw "Trying to call a NULL Object Member Function";
    return ((const_cast<Y *>(_object)->*_function)(a));
  }

  template <class U, class V>
  template <class Y>
  typename type<U>::_t			Functor<U (V)>::Object<Y>::isCallable()	const
  {
    return (_object != NULL && _function != NULL);
  }

  template <class U, class V>
  Functor<U (V)>::Functor()
  : _functor(NULL)
  {}
  
  template <class U, class V>
  Functor<U (V)>::~Functor()
  {}

  template <class U, class V>
  Functor<U (V)>::Functor(Functor<U (V)> const& to_copy)
    : _functor(to_copy._functor)
  {}
  
  template <class U, class V>
  Functor<U (V)>::Functor(expected const& function)
    : _functor(new Function(function))
  {}
  
  template <class U, class V>
  template <class X>
  Functor<U (V)>::Functor(X & object, typename type<U>::_t  (X::*function)(typename type<V>::_t))
    : _functor(new Object<X>(object, function))
  {}

  template <class U, class V>
  Functor<U (V)>		&	Functor<U (V)>::operator=(Functor<U (V)> const&  to_copy)
  {
    _functor = to_copy._functor;
    return (*this);
  }

  template <class U, class V>
  typename type<U>::_t			Functor<U (V)>::operator()(typename type<V>::_t a)				const
  {
    if (_functor == NULL)
      throw "Trying to call a NULL functor";
    return ((*_functor)(a));
  }

  template <class U, class V>
  bool	       	Functor<U (V)>::isCallable()		const
  {
    return (_functor != NULL && _functor->isCallable());
  }
}

#endif
