//
// Bind.hpp for rtype in /home/savari_l//tech3/cpp/Bind
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Thu Jan 31 18:13:53 2013 luca savarino
// Last update Mon Feb  4 00:28:54 2013 luca savarino
//

#ifndef TYPELIST__
# define TYPELIST__

#include "Storage.hpp"

namespace bind
{
  // 0 PARAM

  struct TypeList0 : private Storage0
  {
    TypeList0();
  };
  TypeList0::TypeList0()
  {}

  // 1 PARAM

  template <class T1>
  struct TypeList1 : public Storage1<T1>
  {
    typedef typename	Storage1<T1>				BaseStorageClass;

    TypeList1(typename type::Type<T1>::_t);

    template <class C>
    C	&	operator[](Value<T> & value);
    template <class ReturnType, class Caller, class List>
    ReturnType	operator()();
  };
  template <class T1>
  TypeList1<T1>::TypeList1(typename type::Type<T1>::_t t1)
    : BaseStorageClass(t1)
  {}

  // 2 PARAMS

  template <class T1, class T2>
  struct TypeList2 : public Storage2<T1, T2>
  {
    typedef typename	Storage2<T1, T2>			BaseStorageClass;

    TypeList2(typename type::Type<T1>::_t, typename type::Type<T2>::_t);
  };
  template <class T1, class T2>
  TypeList2<T1, T2>::TypeList2(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2)
    : BaseStorageClass(t1, t2)
  {}

  // 3 PARAMS

  template <class T1, class T2, class T3>
  struct TypeList3 : public Storage3<T1, T2, T3>
  {
    typedef typename	Storage3<T1, T2, T3>			BaseStorageClass;

    TypeList3(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t);
  };
  template <class T1, class T2, class T3>
  TypeList3<T1, T2, T3>::TypeList3(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3)
    : BaseStorageClass(t1, t2, t3)
  {}

  // 4 PARAMS

  template <class T1, class T2, class T3, class T4>
  struct TypeList4 : public Storage4<T1, T2, T3, T4>
  {
    typedef typename	Storage4<T1, T2, T3, T4>		BaseStorageClass;

    TypeList4(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t);
  };
  template <class T1, class T2, class T3, class T4>
  TypeList4<T1, T2, T3, T4>::TypeList4(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4)
    : BaseStorageClass(t1, t2, t3, t4)
  {}

  // 5 PARAMS

  template <class T1, class T2, class T3, class T4, class T5>
  struct TypeList5 : public Storage5<T1, T2, T3, T4, T5>
  {
    typedef typename	Storage5<T1, T2, T3, T4, T5>		BaseStorageClass;

    TypeList5(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t, typename type::Type<T5>::_t);
  };
  template <class T1, class T2, class T3, class T4, class T5>
  TypeList5<T1, T2, T3, T4, T5>::TypeList5(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4, typename type::Type<T5>::_t t5)
    : BaseStorageClass(t1, t2, t3, t4, t5)
  {}

  // 6 PARAMS

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  struct TypeList6 : public Storage6<T1, T2, T3, T4, T5, T6>
  {
    typedef typename	Storage5<T1, T2, T3, T4, T5, T6>	BaseStorageClass;

    TypeList6(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t, typename type::Type<T5>::_t, typename type::Type<T6>::_t);
  };
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  TypeList6<T1, T2, T3, T4, T5, T6>::TypeList6(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4, typename type::Type<T5>::_t t5, typename type::Type<T6>::_t t6)
    : BaseStorageClass(t1, t2, t3, t4, t5, t6)
  {}

}

#endif
