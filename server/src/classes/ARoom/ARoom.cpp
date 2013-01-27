//
// ARoom.cpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 19:12:00 2012 cybil bourely
// Last update Sun Jan 27 19:14:11 2013 luca savarino
//

#include <iostream>
#include "ARoom.hpp"
#include "Client.hpp"

using namespace manageroom;

//
// Client Management
//
// void		ARoom::pushAction(const network::Client *clt)
// {
//   this->_actionQueue.push(clt);
// }

void		ARoom::deleteClient(clientType * clt)
{
  _cltList.remove(clt);
}

void		ARoom::addClient(clientType * clt)
{
  _cltList.push_back(clt);
}

//
// Getteurs
//
unsigned int			ARoom::getReadyPlayer() const
{
  return (_rdyPlayer);
}

unsigned int			ARoom::getNbMaxPlayer() const
{
  return (_nbMaxPlayer);
}

const ARoom::listTaskType	&ARoom::getTaskList() const
{
  return (_taskList);
}

float				ARoom::getTimeOut() const
{
  return (_timeout);
}

const std::string	&ARoom::getName() const
{
  return (_name);
}

unsigned int		ARoom::getNextId()// const
{
  unsigned int		tmp = 0;
  std::list<network::Client *>::iterator	it = _cltList.begin();

  while (it != _cltList.end())
  {
    if ((*it)->getId() != tmp + 1)
    {
      std::cout << "ID assign = " << tmp + 1 << std::endl;
      return (tmp + 1);
    }
    tmp = (*it)->getId();
    ++it;
  }
  return (-1);
}

void		ARoom::addRdyPlayer()
{
  _rdyPlayer++;
}

void		ARoom::setLaunch(bool st)
{
  _launch = st;
}

//
// Constr
//

// bool		ARoom::operator==(const ARoom &room)
// {
//   // if (compare(room._name) == 0)
//   //   return (true);
//   return (false);
// }

ARoom		&ARoom::operator=(const ARoom &cpy)
{
  // this->_actionQueue = cpy._actionQueue;
  _taskList = cpy._taskList;
  _cltList = cpy._cltList;
  _name = cpy._name;
  _rdyPlayer = cpy._rdyPlayer;
  return (*this);
}

ARoom::ARoom(const std::string &name)
  : _name(name), _timeout(0.0), _rdyPlayer(0)
{
//   std::cout << __FUNCTION__ << std::endl;
}

ARoom::ARoom(const ARoom &cpy)
  : _timeout(0.0), _rdyPlayer(0)
{
  *this = cpy;
}



