//
// LinuxSocketUDP.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server/LinuxSocketUDP
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Tue Jan 15 21:58:53 2013 luca savarino
// Last update Mon Jan 28 21:40:40 2013 luca savarino
//

#include <unistd.h>

#include <iostream>
#include <sstream>

#include "LinuxSocketUDP.hpp"

using namespace network;

LinuxSocketUDP::LinuxSocketUDP()
{}

LinuxSocketUDP::LinuxSocketUDP(setsType const& sets)
  : ALinuxSocket(sets)
{}

LinuxSocketUDP::LinuxSocketUDP(LinuxSocketUDP const& to_copy)
  : ALinuxSocket(to_copy)
{}

LinuxSocketUDP::LinuxSocketUDP(int fd, sockaddr_storage const& addr,
			       setsType const& sets)
  : ALinuxSocket(sets, fd), _addr(addr)
{}

LinuxSocketUDP::~LinuxSocketUDP()
{
  if (_fd != -1)
    {
      shutdown(_fd, SHUT_RDWR);
      close(_fd);
    }
}

void		LinuxSocketUDP::initAddrinfo()
{
  _hints.ai_family = AF_INET;
  _hints.ai_socktype = SOCK_DGRAM;
  _hints.ai_flags = 0;
  _hints.ai_protocol = IPPROTO_UDP;
  _hints.ai_canonname = NULL;
  _hints.ai_addr = NULL;
  _hints.ai_next = NULL;
}

LinuxSocketUDP	&	LinuxSocketUDP::operator=(LinuxSocketUDP const& to_copy)
{
  if (_fd != -1)
    close(_fd);
  _addr = to_copy._addr;
  _hints = to_copy._hints;
  ALinuxSocket::operator=(to_copy);
  return (*this);
}

bool			LinuxSocketUDP::bind(int port, std::string const& where, int)
{
  std::ostringstream oss;

  oss << port;
  _hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  if (getaddrinfo(where, oss.str(),
		  &LinuxSocketUDP::hiddenBind, "bind",
		  _hints))
    return (true);
  return (false);
}

bool			LinuxSocketUDP::connect(int port, std::string const& where)
{
  std::ostringstream oss;

  oss << port;
  _hints.ai_flags = 0;
  return (getaddrinfo(where, oss.str(),
		      &LinuxSocketUDP::hiddenConnect, "connect",
		      _hints));
}

int			LinuxSocketUDP::recv(std::string & str, int blockSize)
{
  int			ret;
  char			*rec = new char[blockSize + 1];

  if ((ret = ::recv(_fd, rec, blockSize, MSG_NOSIGNAL)) < -1)
    {
      rec[0] = 0;
      str = rec;
      return (ret);
    }
  rec[ret + 1] = 0;
  str = rec;
  delete [] rec;
  return (ret);
}

int			LinuxSocketUDP::send(std::string const& str)
{
  return (::send(_fd, str.c_str(), str.size(), MSG_NOSIGNAL));
}


bool			LinuxSocketUDP::hiddenConnect(ALinuxSocket &inst,
						      addrinfo &st)
{
  return (::connect(static_cast<LinuxSocketUDP *>(&inst)->_fd,
		    st.ai_addr, st.ai_addrlen) != -1);
}

bool			LinuxSocketUDP::hiddenBind(ALinuxSocket &inst,
						   addrinfo &st)
{
  return (!::bind(static_cast<LinuxSocketUDP *>(&inst)->_fd,
		  st.ai_addr, st.ai_addrlen));
}
