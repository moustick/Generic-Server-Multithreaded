//
// Bind.hpp for rtype in /home/savari_l//tech3/cpp/Bind
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Thu Jan 31 18:13:53 2013 luca savarino
// Last update Sat Feb  2 15:18:03 2013 luca savarino
//

#ifndef STORAGE__
# define STORAGE__

#include "Type.hpp"

namespace bind
{
  // 0 PARAM

  struct Storage0
  {
    Storage0();
  };
  Storage0::Storage0()
  {}

  // 1 PARAM

  template <class T1>
  struct Storage1 : public Storage0
  {
    T1 _t1;

    Storage1(typename type::Type<T1>::_t);
  };
  template <class T1>
  Storage1<T1>::Storage1(typename type::Type<T1>::_t t1)
    : _t1(t1)
  {}

  // 2 PARAMS

  template <class T1, class T2>
  struct Storage2 : public Storage1<T1>
  {
    T2 _t2;

    Storage2(typename type::Type<T1>::_t, typename type::Type<T2>::_t);
  };
  template <class T1, class T2>
  Storage2<T1, T2>::Storage2(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2)
  : Storage1<T1>(t1), _t2(t2)
  {}

  // 3 PARAMS

  template <class T1, class T2, class T3>
  struct Storage3 : public Storage2<T1, T2>
  {
    T3 _t3;

    Storage3(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t);
  };
  template <class T1, class T2, class T3>
  Storage3<T1, T2, T3>::Storage3(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3)
  : Storage2<T1, T2>(t1, t2), _t3(t3)
  {}

  // 4 PARAMS

  template <class T1, class T2, class T3, class T4>
  struct Storage4 : public Storage3<T1, T2, T3>
  {
    T4 _t4;

    Storage4(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t);
  };
  template <class T1, class T2, class T3, class T4>
  Storage4<T1, T2, T3, T4>::Storage4(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4)
  : Storage3<T1, T2, T3>(t1, t2, t3), _t4(t4)
  {}

  // 5 PARAMS

  template <class T1, class T2, class T3, class T4, class T5>
  struct Storage5 : public Storage4<T1, T2, T3, T4>
  {
    T5 _t5;

    Storage5(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t, typename type::Type<T5>::_t);
  };
  template <class T1, class T2, class T3, class T4, class T5>
  Storage5<T1, T2, T3, T4, T5>::Storage5(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4, typename type::Type<T5>::_t t5)
    : Storage4<T1, T2, T3, T4>(t1, t2, t3, t4), _t5(t5)
  {}

  // 6 PARAMS

  template <class T1, class T2, class T3, class T4, class T5, class T6>
  struct Storage6 : public Storage5<T1, T2, T3, T4, T5>
  {
    T6 _t6;

    Storage6(typename type::Type<T1>::_t, typename type::Type<T2>::_t, typename type::Type<T3>::_t, typename type::Type<T4>::_t, typename type::Type<T5>::_t, typename type::Type<T6>::_t);
  };
  template <class T1, class T2, class T3, class T4, class T5, class T6>
  Storage6<T1, T2, T3, T4, T5, T6>::Storage6(typename type::Type<T1>::_t t1, typename type::Type<T2>::_t t2, typename type::Type<T3>::_t t3, typename type::Type<T4>::_t t4, typename type::Type<T5>::_t t5, typename type::Type<T6>::_t t6)
    : Storage5<T1, T2, T3, T4, T5>(t1, t2, t3, t4, t5), _t6(t6)
  {}

}

#endif
