//
// LinuxCondVar.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxCondVar
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 16:38:59 2012 luca savarino
// Last update Wed Jan 16 12:57:56 2013 luca savarino
//

#ifndef LINUXCONDVAR__
# define	LINUXCONDVAR__

#include "ICondVar.hpp"
#include "pthread.h"
#include "SharedPointer.hpp"

namespace	condvar
{
  class	LinuxCondVar : public ICondVar
  {
    typedef	smartpointer::SharedPointer<pthread_cond_t>	condVarType;
    typedef	smartpointer::SharedPointer<pthread_mutex_t>	mutexType;

    condVarType		_condVar;
    mutexType		_mutex;
    bool		_created;

  private :
    void	destroy_both();
    void	destroy_cond();
    void	destroy_mutex();

  public :
    LinuxCondVar();
    LinuxCondVar(LinuxCondVar const&);
    ~LinuxCondVar();

    void	wait();
    void	signal();
    void	broadcast();

    LinuxCondVar &	operator=(LinuxCondVar const&);
  };
}

#endif
