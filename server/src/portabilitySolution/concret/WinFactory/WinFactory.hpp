//
// WinFactory.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:40:43 2012 luca savarino
// Last update Thu Jan 10 17:33:56 2013 luca savarino
//

#ifndef	WINFACTORY__
# define	WINFACTORY__

#include "WinCondVar.hpp"
#include "WinMutex.hpp"
#include "WinSocket.hpp"
#include "WinThread.hpp"

namespace creation
{
  namespace windowscreation
  {
    class	WinFactory
    {
    protected :
      typedef condvar::WinCondVar	CondVar;
      typedef mutex::WinMutex		Mutex;
      typedef socket::WinSocket		Socket;
      typedef thread::WinThread		Thread;
    private :
      WinFactory();
    };
  }
}

#endif
