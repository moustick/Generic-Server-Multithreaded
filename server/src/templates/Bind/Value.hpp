//
// Value.hpp for rtype in /home/savari_l//tech3/cpp/Generic-Server-Multithreaded/server/src/templates/Bind
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Feb  2 15:07:44 2013 luca savarino
// Last update Sat Feb  2 15:29:53 2013 luca savarino
//

#ifndef __VALUE
# define __VALUE

#include "Type.hpp"

namespace bind
{
  template<class T>
  class Value
  {
    T	_value;

  public:
    Value(typename type::Type<T>::_t);
    
    T	&	get();
    T const&	get()	const;
  };
  template<class T>
  Value<T>::Value(typename type::Type<T>::_t value)
    : _value(value)
  {}
  template<class T>
  T	&	get()
  {return(_value);}

  template<class T>
  T const&	get()	const
  {return(_value);}


  template<class T>
  class GetType
  {
    typedef	Value<T>	Type;
  };

  template<class T>
  class TypeTraits
  {};
}

#endif
