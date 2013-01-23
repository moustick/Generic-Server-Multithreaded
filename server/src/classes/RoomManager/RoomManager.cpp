//
// RoomManager.cpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 19:15:31 2012 cybil bourely
// Last update Sun Jan 20 15:49:26 2013 luca savarino
//

#include <string>
#include <iostream>

#include "ARoom.hpp"
#include "RoomManager.hpp"
#include "Client.hpp"
#include "PacketFactory.hpp"
#include "room.hpp"

using namespace manageroom;

RoomManager::RoomManager(unsigned int nbThreadInCache)
  : _threadPool(nbThreadInCache), _isRunning(false), _nbThInCache(nbThreadInCache)
{
  _instrMap[0x0002] = &RoomManager::createRoom;
  _instrMap[0x0003] = &RoomManager::addClient;
  _instrMap[0x0004] = &RoomManager::haveToDeleteRoom;
}

RoomManager::RoomManager(const RoomManager &cpy)
  : _threadPool(cpy._nbThInCache)
{
  *this = cpy;
}

//
// Room Management
//

ARoom		*RoomManager::searchRoom(std::string const& name)
{
  std::list<ARoom *>::iterator	it = _roomList.begin();

  while (it != _roomList.end())
  {
    if ((*it)->getName().compare(name) == 0)
      return (*it);
    ++it;
  }
  return (NULL);
}

void		RoomManager::haveToLaunch(network::Client & clt)
{
  ARoom		*tmp;

  if ((tmp = searchRoom(clt.getRoomName())) != NULL)
  {
    tmp->addRdyPlayer();
    if (tmp->getReadyPlayer() == tmp->getNbMaxPlayer())
      tmp->setLaunch(true);
    Protocol::Packet	*pack = PacketFactory::createOkPacket();
    clt.pushPacketOut(pack);
  }
  clt.pushPacketOut(PacketFactory::createWarningPacket(0x0007));
}

void		RoomManager::createRoom(network::Client & clt)
{
  Protocol::Packet	*packet(clt.frontPacketIn());
  const std::string	room(static_cast<char const*>(packet->getBody())); //====> segfault

  if (searchRoom(room) == NULL)
  {
    _roomList.push_back(new Room(room));
    clt.pushPacketOut(PacketFactory::createOkPacket());
  }
  else
  {
    std::cerr << "This room already exist. Sorry." << std::endl;
    clt.pushPacketOut(PacketFactory::createWarningPacket(0x0007));
  }
  delete packet;
}

void		RoomManager::haveToDeleteRoom(network::Client & clt)
{
  ARoom		*tmp;

  if (searchRoom(clt.getRoomName()) != NULL)
  {
    std::cout << "Delete Room: " << clt.getRoomName() << std::endl;
    _roomList.remove(tmp);
  }
}

//
// Client Management
//

void			RoomManager::addClient(network::Client & clt)
{
  ARoom			*tmp;
  Protocol::Packet	*packet(clt.frontPacketIn());
  const std::string	room(static_cast<char const*>(packet->getBody())); //====> segfault

  if ((tmp = searchRoom(room)) != NULL
      && tmp->getNextId() != -1)
  {
    tmp->addClient(&clt);
    clt.setId(tmp->getNextId());
    clt.setRoomName(room);
    clt.pushPacketOut(PacketFactory::createOkPacket());
    return ;
  }
  clt.pushPacketOut(PacketFactory::createWarningPacket(0x0007));
}

/* ------------- POUR PAPY --------*/

// void		RoomManager::rmClient(network::Client *clt)
// {
//   ARoom		*tmp;

//   if ((tmp = this->searchRoom(clt->getRoomName())) != NULL)
//   {
//     tmp->deleteClient(clt);
//     clt->pushPacketOut(FactoryPacket->createOkPacket());
//     return ;
//   }
//   std::cout << "Room doesn't exist." << std::endl;
//   clt->pushPacketOut(FactoryPacket->createWarningPacket(0x0007));
// }

void				RoomManager::notify(network::Client & clt)
{
  instrMapType::iterator	it;

  if ((it = _instrMap.find(clt.frontPacketOut()->getHeader().getInstruction()))
      != _instrMap.end())
    (this->*(it->second))(clt);
  // APPEL D'UNE FONCTION DE PAPY pour qu'il itere sur les clients de la room
  // ARoom		*tmp;
  // if ((tmp = this->searchRoom(clt->getRoomName())) != NULL)
  // {
  //   tmp->pushAction(clt);
  // }
}

void		RoomManager::setIsRunning(bool isRunning)
{
  _isRunning = isRunning;
}

bool		RoomManager::getIsRunning()
{
  return (_isRunning);
}

//
// Constructor
//
RoomManager	&RoomManager::operator=(const RoomManager &cpy)
{
  _roomList = cpy._roomList;
  _threadPool = cpy._threadPool;
  _isRunning = cpy._isRunning;
  return (*this);
}

RoomManager::RoomManager()
  : _threadPool(4)
{
}

void		RoomManager::cycle()
{
  roomListType::iterator	it;

  if (_isRunning)
    {
      //Mise a jour du Timer
      for (it = _roomList.begin(); it != _roomList.end(); ++it)
	;//_threadPool.pushTask((*it)->getCurrentTask());
      //Sleep
      _threadPool.waitForEnd();
    }
  //destruction des rooms restantes (deconnection clients) 
}
