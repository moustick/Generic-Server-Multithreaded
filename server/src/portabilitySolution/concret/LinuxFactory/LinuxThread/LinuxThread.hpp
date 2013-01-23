//
// LinuxThread.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:03:59 2012 luca savarino
// Last update Sat Dec 22 16:25:39 2012 luca savarino
//

#ifndef LINUXTHREAD__
# define	LINUXTHREAD__

#include <cstdlib>

#include "AThread.hpp"

namespace	thread
{
  class	LinuxThread : public AThread
  {
    void	*_thread;
    void	*_instance;
    bool	_created;

  protected :

    inline void		start_thread();

  public :
    LinuxThread();
    LinuxThread(LinuxThread const&);
    LinuxThread(ptr const&, void * instance = NULL);
    ~LinuxThread();

    void		waitForEnd();
    LinuxThread	&	operator=(LinuxThread const&);
  };
}

#endif
