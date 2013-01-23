//
// LinuxSocketTCP.hpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sun Jan 13 01:26:54 2013 luca savarino
// Last update Wed Jan 16 12:18:00 2013 luca savarino
//

#ifndef	LINUXSOCKETTCP__
# define LINUXSOCKETTCP__

#include "ALinuxSocket.hpp"

namespace network
{
  class LinuxSocketTCP : public ALinuxSocket
  {
  private :
    sockaddr_storage	_addr;
    
  private :
    LinuxSocketTCP(int, sockaddr_storage const&, setsType const&);

    static bool	hiddenConnect(ALinuxSocket &, addrinfo &);
    static bool	hiddenBind(ALinuxSocket &, addrinfo &);
    void	initAddrinfo();

  public :
    LinuxSocketTCP();
    LinuxSocketTCP(setsType const&);
    LinuxSocketTCP(LinuxSocketTCP const&);
    ~LinuxSocketTCP();

    LinuxSocketTCP &	operator=(LinuxSocketTCP const&);

    LinuxSocketTCP	*	accept();

    bool			bind(int, std::string const& where = "", int backlog = SOMAXCONN);
    bool			connect(int, std::string const&);
    int				recv(std::string &, int blockSize);
    int				send(std::string const&);
  };
}

#endif
