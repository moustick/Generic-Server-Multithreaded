
#include "stdafx.h"
#include "WinSock2.h"
#include "WinSock.h"
#include "windows.h"

#include "IUdpSock.hpp"

namespace Socket
{
  class WinUdpSock : IUdpSock
  {
  public:
    WinUdpSock();
    WinUdpSock(const std::string &, short);
    WinUdpSock(const WinUdpSock &);
    ~WinUdpSock();

    WinUdpSock		&operator=(const WinUdpSock &);
    virtual int		accept(void);
    virtual void	send(void *, int);
    virtual void	connect(void);
    virtual int		select(void);


    const std::string	&getIp() const;
    short		getPort() const;
    SOCKET		getSock() const;
    sockaddr_in		&getService() const;

  private:
    const std::string	&_ip;
    short		_port;
    SOCKET		_sock;
    sockaddr_in		service;
    struct sockaddr_in  _cltService;
  };
}
