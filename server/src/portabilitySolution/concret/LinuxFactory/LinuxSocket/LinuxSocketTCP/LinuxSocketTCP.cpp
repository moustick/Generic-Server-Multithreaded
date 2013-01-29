//
// LinuxSocketTCP.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sun Jan 13 01:29:01 2013 luca savarino
// Last update Mon Jan 28 21:38:05 2013 luca savarino
//

#include <unistd.h>

#include <iostream>
#include <sstream>

#include "LinuxSocketTCP.hpp"

using namespace network;

LinuxSocketTCP::LinuxSocketTCP()
{}

LinuxSocketTCP::LinuxSocketTCP(setsType const& sets)
  : ALinuxSocket(sets)
{}

LinuxSocketTCP::LinuxSocketTCP(LinuxSocketTCP const& to_copy)
  : ALinuxSocket(to_copy)
{}

LinuxSocketTCP::LinuxSocketTCP(int fd, sockaddr_storage const& addr,
			       setsType const& sets)
  : ALinuxSocket(sets, fd), _addr(addr)
{}

LinuxSocketTCP::~LinuxSocketTCP()
{
  if (_fd != -1)
    {
      shutdown(_fd, SHUT_RDWR);
      close(_fd);
    }
}

void		LinuxSocketTCP::initAddrinfo()
{
  _hints.ai_family = AF_INET;
  _hints.ai_socktype = SOCK_STREAM;
  _hints.ai_flags = 0;
  _hints.ai_protocol = IPPROTO_TCP;
  _hints.ai_canonname = NULL;
  _hints.ai_addr = NULL;
  _hints.ai_next = NULL;
}

LinuxSocketTCP	&	LinuxSocketTCP::operator=(LinuxSocketTCP const& to_copy)
{
  if (_fd != -1)
    close(_fd);
  _addr = to_copy._addr;
  _hints = to_copy._hints;
  ALinuxSocket::operator=(to_copy);
  return (*this);
}

LinuxSocketTCP	*	LinuxSocketTCP::accept()
{
  sockaddr_storage	addr;
  int			client, val = 1;
  socklen_t		sz = sizeof(addr);

  if ((client = ::accept(_fd, reinterpret_cast<sockaddr *>(&addr),
			 &sz)) != -1)
    {
      setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
      return (new LinuxSocketTCP(client, addr, setsType(3, NULL)));
    }
  std::cerr << "accept error" << std::endl;
  return(NULL);
}

bool			LinuxSocketTCP::bind(int port, std::string const& where, int backlog)
{
  std::ostringstream oss;

  oss << port;
  _hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(where, oss.str(),
		  &LinuxSocketTCP::hiddenBind, "bind",
		  _hints))
    {
      if (::listen(_fd, backlog) != -1)
	return (true);
      else
	{
	  close(_fd);
	  _fd = -1;
	  std::cerr << "listen error" << std::endl;
	}
    }
  return (false);
}

bool			LinuxSocketTCP::connect(int port, std::string const& where)
{
  std::ostringstream oss;

  oss << port;
  _hints.ai_flags = 0;
  return (getaddrinfo(where, oss.str(),
		      &LinuxSocketTCP::hiddenConnect, "connect",
		      _hints));
}

int			LinuxSocketTCP::recv(std::string & str, int blockSize)
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

int			LinuxSocketTCP::send(std::string const& str)
{
  return (::send(_fd, str.c_str(), str.size(), MSG_NOSIGNAL));
}

bool			LinuxSocketTCP::hiddenConnect(ALinuxSocket &inst,
						      addrinfo &st)
{
  return (::connect(static_cast<LinuxSocketTCP *>(&inst)->_fd,
		    st.ai_addr, st.ai_addrlen) != -1);
}

bool			LinuxSocketTCP::hiddenBind(ALinuxSocket &inst,
						   addrinfo &st)
{
  return (!::bind(static_cast<LinuxSocketTCP *>(&inst)->_fd,
		  st.ai_addr, st.ai_addrlen));
}
