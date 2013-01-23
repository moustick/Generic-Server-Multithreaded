//
// LinuxFactory.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:40:43 2012 luca savarino
// Last update Wed Jan 16 12:37:13 2013 luca savarino
//

#ifndef	LINUXFACTORY__
# define	LINUXFACTORY__

#include "LinuxCondVar.hpp"
#include "LinuxMutex.hpp"
#include "LinuxSocketTCP.hpp"
#include "LinuxSocketUDP.hpp"
#include "LinuxThread.hpp"
#include "LinuxClock.hpp"
#include "DLLoaderUnix.hpp"

namespace creation
{
  namespace linuxcreation
  {
    class	LinuxFactory
    {
    protected :
      typedef condvar::LinuxCondVar	CondVar;
      typedef mutex::LinuxMutex		Mutex;
      typedef network::ALinuxSocket	Socket;
      typedef network::LinuxSocketTCP	SocketTCP;
      typedef network::LinuxSocketUDP	SocketUDP;
      typedef thread::LinuxThread		Thread;
      typedef dclock::LinuxClock		Timer; //TEST
      typedef loader::LinuxDllLoader	Loader;
    private :
      LinuxFactory();
    };
  }
}

#endif
