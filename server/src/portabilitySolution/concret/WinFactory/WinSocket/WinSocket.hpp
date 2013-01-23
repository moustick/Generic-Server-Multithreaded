//
// WinSocket.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinSocket
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:50:08 2012 luca savarino
// Last update Wed Jan 16 19:13:09 2013 luca savarino
//

#ifndef WINSOCKET__
# define	WINSOCKET__

#include "ISocket.hpp"

namespace	socket
{
  class	WinSocket : public network::ISocket
  {
  public :
    WinSocket();
    ~WinSocket();
  };
}

#endif
