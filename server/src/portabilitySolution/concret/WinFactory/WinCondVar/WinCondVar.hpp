//
// WinCondVar.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinCondVar
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:43:48 2012 luca savarino
// Last update Wed Dec 19 17:43:49 2012 luca savarino
//

#ifndef WINCONDVAR__
# define	WINCONDVAR__

#include "ICondVar.hpp"
#include <windows.h>

namespace	condvar
{
  class	WinCondVar : public ICondVar
  {
    typedef	smartpointer::SharedPointer<CONDITION_VARIABLE>		condVarType;
    typedef	smartpointer::SharedPointer<HANDLE>			mutexType;

    BOOL		_created;
    condVarType		_condVar;
    mutexType		_mutex;

  public :
    WinCondVar();
    ~WinCondVar();
  };
}

#endif
