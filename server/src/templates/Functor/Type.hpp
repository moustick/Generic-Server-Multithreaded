//
// Type.hpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/RoomManager/Functor
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 05:14:40 2013 luca savarino
// Last update Mon Jan 14 05:15:10 2013 luca savarino
//

#ifndef TYPE__
# define TYPE__

namespace functor
{
    template <class T2, bool U2>
    struct	type_base
    {};

    template <class T2>
    struct	type_base<T2, true>
    {
      typedef	T2	&	_t;
      typedef	T2	const&	_const_t;
    };
    template <class T2>
    struct	type_base<T2, false>
    {
      typedef 	T2		_t;
      typedef 	T2	const	_const_t;
    };

    template <class T2>
    struct	type : public type_base<T2, (sizeof(T2) > sizeof(int))>
    {};
    template <>
    struct	type<void>
    {
      typedef	void		_t;
    };
}

#endif
