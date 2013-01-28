//
// ALinuxSocket.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 01:45:36 2013 luca savarino
// Last update Mon Jan 28 15:25:29 2013 luca savarino
//

#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "ALinuxSocket.hpp"

using namespace network;

ALinuxSocket::ALinuxSocket()
  : _fd(-1), _sets(setsType(3))
{}

ALinuxSocket::ALinuxSocket(setsType const& sets, int fd)
  : _fd(fd), _sets(sets)
{}

ALinuxSocket::ALinuxSocket(ALinuxSocket const& to_copy)
  : _hints(to_copy._hints), _fd(to_copy._fd), _sets(to_copy._sets)
{}

ALinuxSocket::~ALinuxSocket()
{}

ALinuxSocket	&		ALinuxSocket::operator=(ALinuxSocket const& to_copy)
{
  _fd = to_copy._fd;
  _sets = to_copy._sets;
  return (*this);
}

int				ALinuxSocket::getFd()	const
{
  return (_fd);
}

void				ALinuxSocket::initAddrinfo()
{
  memset(&_hints, 0, sizeof(_hints));
}

bool				ALinuxSocket::getaddrinfo(std::string const& where,
							  std::string const& port,
							  ptr fct,
							  std::string const & name,
							  addrinfo & hints)
{
  int				ret, val = 1;
  addrinfo			*result;

  initAddrinfo();
  if ((ret = ::getaddrinfo((where == "") ? (NULL) : (where.c_str()), port.c_str(), &hints, &result)))
    std::cerr << "getaddrinfo error :" << std::endl;
  for (addrinfo *tmp = result; tmp != NULL; tmp = tmp->ai_next)
    if ((_fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) != -1)
      if (fct(*this, *result)
	  && !setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)))
	{
	  freeaddrinfo(result);
	  return (true);
	}
      else
	close(_fd);
    else
      std::cerr << "socket : error" << std::endl;
  freeaddrinfo(result);
  std::cerr << name << " error" << std::endl;
  return (false);
}

void				ALinuxSocket::setSets(setsType & sets)
{
  _sets = sets;
}

ALinuxSocket::setsType		const&	ALinuxSocket::getSets()		const
{
  return (_sets);
}
