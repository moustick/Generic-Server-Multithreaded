//
// ALinuxSocket.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 01:45:36 2013 luca savarino
// Last update Sun Jan 20 22:16:41 2013 luca savarino
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

int				ALinuxSocket::getMaxFd(listType	& toSelectList)
{
  int				ret = 0, currFd, i;
  listType::const_iterator	it;

  for (it = toSelectList.begin(); it != toSelectList.end(); ++it)
    if (testSets((*it)->_sets))
      {
	currFd = (*it)->_fd;
	if (currFd > ret)
	  ret = (*it)->_fd;
      }
  return (ret);
}

void				ALinuxSocket::initAddrinfo()
{
  memset(&_hints, 0, sizeof(_hints));
}

int				ALinuxSocket::initSets(listType	const& toSelectList,
						       std::vector<fd_set> & sets)
{
  int				ret = 0, currFd, i;
  listType::const_iterator	it;

  for (i = 0; i < sets.size(); ++i)
    FD_ZERO(&(sets[i]));
  for (it = toSelectList.begin(); it != toSelectList.end(); ++it)
    if (testSets((*it)->_sets))
      {
	currFd = (*it)->_fd;
	if (currFd > ret)
	  ret = (*it)->_fd;
	for (i = 0; i < sets.size(); ++i)
	  if ((*it)->_sets[i].isCallable())
	    FD_SET((*it)->_fd, &sets[i]);
      }
  return (ret);
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

bool				ALinuxSocket::testSets(setsType & sets)
{
  int				i;
  
  for (i = 0; i < sets.size(); ++i)
    if (sets[i].isCallable())
      return (true);
  return (false);
}

bool				ALinuxSocket::select(listType	& toSelectList, callbackType & callback)
{
  int				maxFd, selected, i, prevSize = toSelectList.size();
  std::vector<fd_set>		sets(3);
  listType::iterator		it;
  functorType			tmp;
  
  while (1)
    {
      maxFd = initSets(toSelectList, sets) + 1;
      if ((selected = ::select(maxFd, &sets[0], &sets[1], &sets[2], NULL)) == -1)
	{
	  std::cerr << "select error" << std::endl;
	  return (false);
	}
      for (it = toSelectList.begin();
      	   selected && it != toSelectList.end();
      	   ++it)
      	for(i = 0; i < sets.size(); ++i)
      	  {
      	    if ((*it)->_sets[i].isCallable())
      	      if (FD_ISSET((*it)->_fd, &sets[i]))
      		{
		  tmp = (*it)->_sets[i];
      		  if (!tmp(toSelectList, it))
		    return (true);
      		  if (!(--selected) || it == toSelectList.end())
		    break;
      		}
      	  }
      if (callback.isCallable())
	callback();
    }
  return (true);
}
