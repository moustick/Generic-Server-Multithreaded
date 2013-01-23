//
// SharedPointerBase.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/SharedPointerBases
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Sun Dec 23 03:32:55 2012 luca savarino
//

#ifndef SHAREDPOINTERBASE__
# define	SHAREDPOINTERBASE__

#include "ReferenceCounter.hpp"

namespace smartpointer
{
  template <class T>
  class	SharedPointerBase
  {
  protected :
    T			*_ptr;
    ReferenceCounter	*_counter;

  public :
    SharedPointerBase(T const* ptr = NULL);
    SharedPointerBase(T const&);
    SharedPointerBase(SharedPointerBase<T> const&);
    ~SharedPointerBase();

    SharedPointerBase<T>	&	operator=(SharedPointerBase<T> const&);
    bool				operator==(SharedPointerBase<T> const&);
    bool				operator==(T const*);
    bool				operator!=(SharedPointerBase<T> const&);
    bool				operator!=(T const*);
    T				&	operator*();
    T				const&	operator*()				const;
    T				*	operator->();
    T				const*	operator->()				const;

    void				destroy();
    T				*	getPointer();
    T				const*	getPointer()				const;
  };

  template <class T>
  SharedPointerBase<T>::SharedPointerBase(T const* ptr)
    : _ptr(const_cast<T *>(ptr)), _counter(new ReferenceCounter)
  {}

  template <class T>
  SharedPointerBase<T>::SharedPointerBase(T const& ptr)
    : _ptr(ptr), _counter(new ReferenceCounter)
  {}

  template <class T>
  SharedPointerBase<T>::SharedPointerBase(SharedPointerBase<T> const& to_copy)
    : _ptr(to_copy._ptr)
  {
    if (_ptr !=  NULL)
      {
	_counter = to_copy._counter;
	++(*_counter);
      }
    else
      _counter = new ReferenceCounter;
  }

  template <class T>
  SharedPointerBase<T>::~SharedPointerBase()
  {
    destroy();
  }

  template <class T>
  SharedPointerBase<T>	&		SharedPointerBase<T>::operator=(SharedPointerBase<T> const& to_copy)
  {
    if (this == &to_copy)
      return (*this);
    destroy();
    if ((_ptr = to_copy._ptr) == NULL)
      {
	_counter = new ReferenceCounter;
	return (*this);
      }
    _counter = to_copy._counter;
    ++(*_counter);
    return (*this);
  }

  template <class T>
  bool					SharedPointerBase<T>::operator==(SharedPointerBase<T> const& to_cmp)
  {
    return (to_cmp._ptr == _ptr);
  }

  template <class T>
  bool					SharedPointerBase<T>::operator==(T const* to_cmp)
  {
    return (to_cmp == _ptr);
  }

  template <class T>
  bool					SharedPointerBase<T>::operator!=(SharedPointerBase<T> const& to_cmp)
  {
    return (to_cmp._ptr != _ptr);
  }

  template <class T>
  bool					SharedPointerBase<T>::operator!=(T const* to_cmp)
  {
    return (to_cmp != _ptr);
  }

  template <class T>
  T			&		SharedPointerBase<T>::operator*()
  {
    return (*_ptr);
  }

  template <class T>
  T			const&		SharedPointerBase<T>::operator*()	const
  {
    return (*_ptr);
  }

  template <class T>
  T			*		SharedPointerBase<T>::operator->()
  {
    if (_ptr == NULL)
      throw "Trying to use a NULL pointer";
    return (_ptr);
  }

  template <class T>
  T			const*		SharedPointerBase<T>::operator->()	const
  {
    if (_ptr == NULL)
      throw "Trying to use a NULL pointer";
    return (_ptr);
  }

  template <class T>
  void					SharedPointerBase<T>::destroy()
  {
    if (!(--(*_counter)).getValue())
      {
	if (_ptr != NULL)
	  delete _ptr;
	delete _counter;
      }
  }

  template <class T>
  T			*		SharedPointerBase<T>::getPointer()
  {
    return (_ptr);
  }

  template <class T>
  const T		*		SharedPointerBase<T>::getPointer()	const
  {
    return (_ptr);
  }
}

#endif
