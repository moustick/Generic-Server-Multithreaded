//
// Functor.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/functors
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Wed Jan 16 14:13:34 2013 luca savarino
//

#ifndef FUNCTOR__
# define	FUNCTOR__

#include <exception>

#include "Type.hpp"
#include "SharedPointerBase.hpp"

namespace functor
{
  template <class T = void()>
  class	Functor;

  template <class U>
  class	Functor<U ()>
  {
  public :

    typedef	typename type<U>::_t	(*expected)();

  private :
    class INestedFunctor
    {
    public :
      virtual			~INestedFunctor();

      virtual typename type<U>::_t	operator()() = 0;
      virtual bool			isCallable()	const = 0;
    };

    class Function : public INestedFunctor
    {
      expected		_function;

    public :
      Function(Function const&);
      Function(expected const&);
      ~Function();
      
      typename type<U>::_t		operator()();
      bool				isCallable()	const;
    };
    template <class Y>
    class Object : public INestedFunctor
    {
    public :
      typedef typename type<U>::_t		(Y::*expected2)();
    private :
      Y		const			*_object;
      expected2				_function;
    public :
      Object(Object const&);
      Object(Y const&, expected2 const& function = &Y::operator());
      ~Object();
      
      typename type<U>::_t		operator()();
      bool				isCallable()	const;
    };

    smartpointer::SharedPointerBase<INestedFunctor>		_functor;

  public :
    Functor();
    Functor(Functor<U ()> const&);
    Functor(expected const&);
    template <class X>
    Functor(X & object, typename type<U>::_t  (X::*function)() = &X::operator());
    ~Functor();

    Functor<U ()>		&			operator=(Functor<U ()> const&);
    typename type<U>::_t				operator()();
    bool						isCallable();
  };

  template <class T>
  class	Functor : public Functor<T>
  {};

  template <class U>
  Functor<U ()>::INestedFunctor::~INestedFunctor()
  {}

  template <class U>
  Functor<U ()>::Function::Function(Function const& to_copy)
    : _function(to_copy._function)
  {}
  
  template <class U>
  Functor<U ()>::Function::Function(expected const& function)
    : _function(function)
  {}

  template <class U>
  Functor<U ()>::Function::~Function()
  {}
  
  template <class U>
  typename type<U>::_t		Functor<U ()>::Function::operator()()
  {
    if (_function == NULL)
      throw "Trying to call a NULL function";
    return (_function());
  }

  template <class U>
  bool				Functor<U ()>::Function::isCallable()	const
  {
    return (_function != NULL);
  }

  template <class U>
  template <class Y>
  Functor<U ()>::Object<Y>::Object(Object const& to_copy)
    : _object(to_copy._object), _function(to_copy._function)
  {}
  
  template <class U>
  template <class Y>
  Functor<U ()>::Object<Y>::Object(Y const& object, expected2 const& function)
    : _object(&object), _function(function)
  {}
  
  template <class U>
  template <class Y>
  Functor<U ()>::Object<Y>::~Object()
  {}

  template <class U>
  template <class Y>
  typename type<U>::_t			Functor<U ()>::Object<Y>::operator()()
  {
    if (_function == NULL)
      throw "Trying to call a NULL Object Member Function";
    return ((const_cast<Y *>(_object)->*_function)());
  }

  template <class U>
  template <class Y>
  bool			Functor<U ()>::Object<Y>::isCallable()	const
  {
    return (_object != NULL && _function != NULL);
  }

  template <class U>
  Functor<U ()>::Functor()
  : _functor(NULL)
  {}
  
  template <class U>
  Functor<U ()>::~Functor()
  {}

  template <class U>
  Functor<U ()>::Functor(Functor<U ()> const& to_copy)
    : _functor(to_copy._functor)
  {}
  
  template <class U>
  Functor<U ()>::Functor(expected const& function)
    : _functor(new Function(function))
  {}
  
  template <class U>
  template <class X>
  Functor<U ()>::Functor(X & object, typename type<U>::_t  (X::*function)())
    : _functor(new Object<X>(object, function))
  {}

  template <class U>
  Functor<U ()>		&	Functor<U ()>::operator=(Functor<U ()> const&  to_copy)
  {
    _functor = to_copy._functor;
    return (*this);
  }

  template <class U>
  typename type<U>::_t			Functor<U ()>::operator()()
  {
    if (_functor == NULL)
      throw "Trying to call a NULL functor";
    return ((*_functor)());
  }

  template <class U>
  bool	       	Functor<U ()>::isCallable()
  {
    return (_functor != NULL && _functor->isCallable());
  }
}

#endif
