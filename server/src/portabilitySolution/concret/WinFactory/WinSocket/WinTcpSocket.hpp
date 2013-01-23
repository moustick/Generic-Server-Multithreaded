
#include "stdafx.h"
#include "WinSock2.h"
#include "WinSock.h"
#include "windows.h"

#include "ITcpSock.hpp"

namespace Socket
{
  class WinTcpSock : ITcpSock
  {
  public:
    WinTcpSock();
    WinTcpSock(const std::string &, short);
    WinTcpSock(const WinTcpSock &);
    ~WinTcpSock();

    WinTcpSock		&operator=(const WinTcpSock &);
    virtual int		accept(void);
    virtual void	send(void *, int);
    virtual void	connect(void);
    virtual int		select(void);
    virtual void	bind(void);


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
