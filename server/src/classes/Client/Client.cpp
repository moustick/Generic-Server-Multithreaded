//
// Client.cpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 19:10:38 2012 cybil bourely
// Last update Sun Jan 27 19:15:23 2013 luca savarino
//

#include <iostream>
#include "Client.hpp"
#include "IObserver.hpp"

using namespace network;

Client::Client()
{}

Client::Client(manageroom::IObserver *roomManager)
  : _roomManager(roomManager), _boolState(false)
{}

Client::~Client()
{}

Client::Client(const Client &cpy)
{
  *this = cpy;
}

void		Client::setRoomManager(manageroom::IObserver *roomManager)
{
  _roomManager = roomManager;
}

void		Client::pushPacketIn(Protocol::Packet *packet)
{
  _mutex->lock();
  _msgQueueIn.push(packet);
  _mutex->unlock();
  _roomManager->notify(*this);
}

void		Client::pushPacketOut(Protocol::Packet *pack)
{
  _mutex->lock();
  _msgQueueOut.push(pack);
  _mutex->unlock();
}

Protocol::Packet	*Client::popPacketIn()
{
  Protocol::Packet	*ret = NULL;

  _mutex->lock();
  ret = _msgQueueIn.front();
  _msgQueueIn.pop();
  _mutex->unlock();
  return (ret);
}

Protocol::Packet	*	Client::popPacketOut()
{
  Protocol::Packet	*ret;

  _mutex->lock();
  ret = _msgQueueOut.front();
  _msgQueueOut.pop();
  _mutex->unlock();
  return (ret);
}

Protocol::Packet	*	Client::frontPacketOut()
{
  Protocol::Packet	*ret;

  _mutex->lock();
  // ret = new Protocol::Packet(*_msgQueueOut.front());
  _mutex->unlock();
  return (ret);
}

Protocol::Packet	*	Client::frontPacketIn()
{
  Protocol::Packet	*ret;

  _mutex->lock();
  // ret = new Protocol::Packet(*_msgQueueIn.front());
  _mutex->unlock();
  return (ret);
}

//
// Getteurs / Setteurs
//

bool                                          Client::getBoolState()
{
    return _boolState;
}

void                                          Client::setBoolState()
{
    _boolState = true;
}

unsigned int	Client::getId() const
{
  return (_id);
}

std::string	Client::getRoomName() const
{
  return (_roomName);
}

void		Client::setRoomName(const std::string &name)
{
  _roomName = name;
}

void		Client::setId(unsigned int id)
{
  _id = id;
}

//
// Constr / Destr
//
Client		&Client::operator=(const Client &cpy)
{
  _roomManager = cpy._roomManager;
  _id = cpy._id;
  _packet = cpy._packet;
  _roomName = cpy._roomName;
  _mutex = cpy._mutex;
  _sets = cpy._sets;
  _res = cpy._res;
  return (*this);
}
