//
// SharedPointer.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/SharedPointers
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Fri Jan 18 19:31:20 2013 luca savarino
//

#ifndef SHAREDPOINTER__
# define	SHAREDPOINTER__

#include "Functor.hpp"

namespace smartpointer
{
  template <class T, class U = void()>
  class	SharedPointer : public SharedPointerBase<T>
  {
  public  :
    typedef	functor::Functor<U>		fctType;
    typedef	functor::Functor<U>	&	fctTypeRef;
    typedef	functor::Functor<U>	const&	const_fctTypeRef;

  private :
    fctType		_fct;

  public :
    SharedPointer(T const* ptr = NULL);
    SharedPointer(T const&);
    SharedPointer(const_fctTypeRef fct, T const* ptr = NULL);
    SharedPointer(SharedPointer<T, U> const&);
    SharedPointer(const_fctTypeRef  fct, T const&);
    ~SharedPointer();

    SharedPointer<T, U>	&	operator=(SharedPointer<T, U> const&);

    void			destroy();
    void			setFct(const_fctTypeRef);
  };

  template <class T, class U>
  SharedPointer<T, U>::SharedPointer(T const* ptr)
    : SharedPointerBase<T>(ptr), _fct(NULL)
  {}

  template <class T, class U>
  SharedPointer<T, U>::SharedPointer(T const& ptr)
    :  SharedPointerBase<T>(ptr), _fct(NULL)
  {}

  template <class T, class U>
  SharedPointer<T, U>::SharedPointer(const_fctTypeRef fct, T const* ptr)
    :  SharedPointerBase<T>(ptr), _fct(fct)
  {}

  template <class T, class U>
  SharedPointer<T, U>::SharedPointer(SharedPointer<T, U> const& to_copy)
    : SharedPointerBase<T>(to_copy), _fct(to_copy._fct)
  {}

  template <class T, class U>
  SharedPointer<T, U>::SharedPointer(const_fctTypeRef fct, T const& ptr)
    :  SharedPointerBase<T>(ptr), _fct(fct)
  {}

  template <class T, class U>
  SharedPointer<T, U>::~SharedPointer()
  {
    destroy();
  }

  template <class T, class U>
  SharedPointer<T, U>	&		SharedPointer<T, U>::operator=(SharedPointer<T, U> const& to_copy)
  {
    if (this == &to_copy)
      return (*this);
    destroy();
    SharedPointerBase<T>::operator=(to_copy);
    _fct = to_copy._fct;
    return (*this);
  }

  template <class T, class U>
  void				SharedPointer<T, U>::destroy()
  {
    if (SharedPointerBase<T>::_counter->getValue() == 1)
      _fct();
  }

  template <class T, class U>
  void				SharedPointer<T, U>::setFct(const_fctTypeRef fct)
  {
    _fct = fct;
  }
}

#endif
