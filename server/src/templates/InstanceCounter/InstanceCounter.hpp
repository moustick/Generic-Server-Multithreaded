//
// InstanceCounter.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/InstanceCounters
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Sun Dec 23 03:32:55 2012 luca savarino
//

#ifndef INSTANCECOUNTER__
# define	INSTANCECOUNTER__

template <class T>
class	InstanceCounter
{
protected :
  static int	counter = 0;

protected :
  InstanceCounter(){++counter;}
  ~InstanceCounter(){--counter};
};

#endif
