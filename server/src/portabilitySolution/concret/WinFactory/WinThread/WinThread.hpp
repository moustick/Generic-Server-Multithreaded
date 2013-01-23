//
// WinThread.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:52:11 2012 luca savarino
// Last update Wed Dec 19 17:52:24 2012 luca savarino
//

#ifndef WINTHREAD__
# define	WINTHREAD__ 

#include "AThread.hpp"

namespace	thread
{
  class	WinThread : public AThread
  {
    void		*_thread;

  protected :

    inline void		start_thread();

  public :
    WinThread();
    WinThread(WinThread const&);
    WinThread(ptr);
    ~WinThread();

    void	waitforend();
  };
}

#endif
