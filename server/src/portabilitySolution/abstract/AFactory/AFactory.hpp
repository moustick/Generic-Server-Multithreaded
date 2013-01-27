//
// AFactory.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/AFactory
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:56:28 2012 luca savarino
// Last update Sun Jan 27 18:57:35 2013 luca savarino
//

#ifndef	AFACTORY__
# define	AFACTORY__

#include "Factories.hpp"

namespace creation
{
  class	AFactory : private Factory
  {
  public:
    typedef Factory::CondVar	CondVar;
    typedef Factory::Mutex	Mutex;
    typedef Factory::Socket	Socket;
    typedef Factory::SocketTCP	SocketTCP;
    typedef Factory::SocketUDP	SocketUDP;
    typedef Factory::Thread	Thread;

    static	condvar::ICondVar	*	getCondVar();
    static	mutex::IMutex		*	getMutex();
    static	thread::AThread		*	getThread();
  private :
    AFactory();
  };

  typedef AFactory::CondVar		CondVar;
  typedef AFactory::Mutex		Mutex;
  typedef AFactory::Socket		Socket;
  typedef AFactory::SocketTCP		SocketTCP;
  typedef AFactory::SocketUDP		SocketUDP;
  typedef AFactory::Thread		Thread;
}

#endif
