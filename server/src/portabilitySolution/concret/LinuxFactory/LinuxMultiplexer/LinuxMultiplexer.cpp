//
// LinuxMultiplexer.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 01:45:36 2013 luca savarino
// Last update Mon Jan 28 17:43:32 2013 luca savarino
//

#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "ALinuxSocket.hpp"
#include "LinuxMultiplexer.hpp"

using namespace network;

LinuxMultiplexer::LinuxMultiplexer()
{}

LinuxMultiplexer::LinuxMultiplexer(LinuxMultiplexer const&)
{}

LinuxMultiplexer::~LinuxMultiplexer()
{}

LinuxMultiplexer	&		LinuxMultiplexer::operator=(LinuxMultiplexer const&)
{
  return (*this);
}

int				LinuxMultiplexer::getMaxFd(listType	& toSelectList)
{
  int				ret = 0, currFd;
  listType::const_iterator	it;

  for (it = toSelectList.begin(); it != toSelectList.end(); ++it)
    if (testSets((*it)->getSets()))
      {
	currFd = (*it)->getFd();
	if (currFd > ret)
	  ret = (*it)->getFd();
      }
  return (ret);
}

int				LinuxMultiplexer::initSets(listType	const& toSelectList,
						       std::vector<fd_set> & sets)
{
  int				ret = 0, currFd;
  unsigned int			i;
  listType::const_iterator	it;

  for (i = 0; i < sets.size(); ++i)
    FD_ZERO(&(sets[i]));
  for (it = toSelectList.begin(); it != toSelectList.end(); ++it)
    if (testSets((*it)->getSets()))
      {
	currFd = (*it)->getFd();
	if (currFd > ret)
	  ret = currFd;
	for (i = 0; i < sets.size(); ++i)
	  if ((*it)->getSets()[i].isCallable())
	    FD_SET(currFd, &sets[i]);
      }
  return (ret);
}


bool				LinuxMultiplexer::testSets(setsType const& sets)
{
  unsigned int			i;
  
  for (i = 0; i < sets.size(); ++i)
    if (sets[i].isCallable())
      return (true);
  return (false);
}

bool				LinuxMultiplexer::start(listType	& toSelectList,
							callbackType const& callback)
{
  int				maxFd, selected;
  unsigned int			i;
  std::vector<fd_set>		sets(3);
  listType::iterator		it;
  
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
	  if ((*it)->getSets()[i].isCallable())
	    if (FD_ISSET((*it)->getFd(), &sets[i]))
	      {
		if (!(((*it)->getSets()[i])(toSelectList, it)))
		  return (true);
		else if (!(--selected) || it == toSelectList.end())
		  break;
	      }
      if (callback.isCallable())
	callback();
    }
  return (true);
}
