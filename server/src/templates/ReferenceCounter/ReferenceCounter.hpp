//
// ReferenceCounter.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/ReferenceCounters
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Sun Dec 23 03:32:55 2012 luca savarino
//

#ifndef REFERENCECOUNTER__
# define	REFERENCECOUNTER__

#include <ostream>

namespace	smartpointer
{
  class	ReferenceCounter
  {
    int	_value;

  public :
    ReferenceCounter();
    ReferenceCounter(ReferenceCounter const&);
    ~ReferenceCounter();

    ReferenceCounter	&	operator=(ReferenceCounter const&);
    ReferenceCounter	&	operator++();
    ReferenceCounter	&	operator++(int);
    ReferenceCounter	&	operator--();
    ReferenceCounter	&	operator--(int);

    int				getValue()				const;
  };
}

#endif
