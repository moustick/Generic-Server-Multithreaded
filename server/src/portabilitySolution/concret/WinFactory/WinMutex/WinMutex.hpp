//
// WinMutex.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinMutex
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:45:00 2012 luca savarino
// Last update Wed Dec 19 17:45:31 2012 luca savarino
//

#ifndef WINMUTEX__
# define	WINMUTEX__

#include "IMutex.hpp"
#include "SharedPointer.hpp"
#include <windows.h>

namespace	mutex
{
  class	WinMutex : IMutex
  {
    typedef	smartpointer::SharedPointer<HANDLE>	mutexType;
    BOOL		_created;
    CRITICAL_SECTION	CriticalSection;
    mutexType		_mutex;

  private:
    void	destroy_mutex();

  public :
    WinMutex();
    WinMutex(WinMutex const&);
    ~WinMutex();
    
    void	lock();
    void	unlock();
    BOOL	trylock();
 };
}

#endif
