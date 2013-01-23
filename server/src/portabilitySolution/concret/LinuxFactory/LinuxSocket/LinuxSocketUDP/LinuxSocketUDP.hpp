//
// LinuxSocketUDP.hpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sun Jan 13 01:26:54 2013 luca savarino
// Last update Wed Jan 16 12:54:31 2013 luca savarino
//

#ifndef	LINUXSOCKETUDP__
# define LINUXSOCKETUDP__

#include <string>

#include "ALinuxSocket.hpp"

namespace network
{
  class LinuxSocketUDP : public ALinuxSocket
  {
  private :
    sockaddr_storage	_addr;
    
  private :
    LinuxSocketUDP(int, sockaddr_storage const&, setsType const&);

    static bool	hiddenConnect(ALinuxSocket &, addrinfo &);
    static bool	hiddenBind(ALinuxSocket &, addrinfo &);
    void	initAddrinfo();

  public :
    LinuxSocketUDP();
    LinuxSocketUDP(setsType const&);
    LinuxSocketUDP(LinuxSocketUDP const&);
    ~LinuxSocketUDP();

    LinuxSocketUDP &	operator=(LinuxSocketUDP const&);

    bool			bind(int, std::string const& where = "", int backlog = SOMAXCONN);
    bool			connect(int, std::string const&);
    int				recv(std::string &, int blockSize);
    int				send(std::string const&);
  };
}

#endif
