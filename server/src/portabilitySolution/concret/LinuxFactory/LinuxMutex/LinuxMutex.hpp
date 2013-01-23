//
// LinuxMutex.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxMutex
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:00:24 2012 luca savarino
// Last update Wed Jan 16 12:57:24 2013 luca savarino
//

#ifndef LINUXMUTEX__
# define	LINUXMUTEX__

#include <pthread.h>

#include "IMutex.hpp"
#include "SharedPointer.hpp"

namespace	mutex
{
  class	LinuxMutex : public IMutex
  {
    typedef	smartpointer::SharedPointer<pthread_mutex_t>	mutexType;

    mutexType	_mutex;
    bool	_created;

  private :
    void  destroy_mutex();

  public :
    LinuxMutex();
    LinuxMutex(LinuxMutex const&);
    ~LinuxMutex();

    void	lock();
    void	unlock();
    bool	trylock();
  };
}

#endif
