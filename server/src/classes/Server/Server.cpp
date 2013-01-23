//
// Server.cpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/Server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan 16 22:31:08 2013 luca savarino
// Last update Sun Jan 20 21:48:55 2013 luca savarino
//

#include "Buffer.hpp"
#include "Client.hpp"
#include "IObserver.hpp"
#include "Protocol.hpp"
#include "RoomManager.hpp"
#include "Serialize.hpp"
#include "Server.hpp"

#include <iostream>

using namespace network;

Server::Server(int tcpEntryPoint,
	       int udpEntryPoint,
	       int maxClientNbr)
  : _tcpEntryPoint(tcpEntryPoint),
    _udpEntryPoint(udpEntryPoint),
    _maxClientNbr((maxClientNbr <= (INT_MAX - 3)) ?
		  maxClientNbr : (INT_MAX - 3))
{
  creation::Socket::setsType		sets(3, NULL);
  creation::SocketTCP			*tcpServer;
  creation::SocketUDP			*udpServer;

  sets[0] = ALinuxSocket::functorType(*this,
				      &Server::tcpConnectionManager);
  (tcpServer = new creation::SocketTCP(sets))->bind(tcpEntryPoint);
  sets[0] = ALinuxSocket::functorType(*this,
  				      &Server::commonRecvManager);
  (udpServer = new creation::SocketUDP(sets))->bind(udpEntryPoint);
  _ClientList.push_back(tcpServer);
  _ClientList.push_back(udpServer);
  _roomManager = new manageroom::RoomManager(4);
}

Server::Server(Server const& to_copy)
  : _tcpEntryPoint(to_copy._tcpEntryPoint),
    _udpEntryPoint(to_copy._udpEntryPoint),
    _ClientList(to_copy._ClientList),
    _ClientMap(to_copy._ClientMap),
    _maxClientNbr(to_copy._maxClientNbr)
{}

Server	&	Server::operator=(Server const& to_copy)
{
  _tcpEntryPoint = to_copy._tcpEntryPoint;
  _udpEntryPoint = to_copy._udpEntryPoint;
  _ClientList = to_copy._ClientList;
  _ClientMap = to_copy._ClientMap;
  _maxClientNbr = to_copy._maxClientNbr;

  return (*this);
}

Server::~Server()
{
  ClientListType::iterator	it;

  for(it = _ClientList.begin(); it != _ClientList.end(); ++it)
    delete *it;
  delete _roomManager;
}

void		Server::setRoomManager(manageroom::IObserver *roomManager)
{
  _roomManager = roomManager;
}

Protocol::Packet	*Server::getNextPacket(buffer::Buffer &buff) const
{
  Protocol::Header	*header;
  Protocol::Packet	*packet;
  std::string		head;
  std::string		body;

  if (buff.getPiece(head, 5).size() == 5)
  {
    header = Protocol::Serialize::DeserializeHeader(head.c_str());
    if (buff.pop(body, header->getBodySize()).size() == header->getBodySize())
      packet = Protocol::Serialize::Deserialize((head + body).c_str());
    delete header;
    return (packet);
  }
  return (NULL);
}

bool			Server::start()
{
  creation::Socket::callbackType	callback = creation::Socket::callbackType(*static_cast<manageroom::RoomManager*>(_roomManager), &manageroom::RoomManager::cycle);
  
  return(creation::Socket::select(_ClientList,callback));
}

bool			Server::tcpConnectionManager(ClientListType & list,
						     ClientListType::iterator & it)
{
  creation::Socket::setsType		sets(3, NULL);
  creation::Socket			*socket;

  std::cout << "new client" << std::endl;
  if ((socket = static_cast<network::LinuxSocketTCP *>(*it)->accept()) != NULL)
    {
      if (list.size() == _maxClientNbr)
	{
	  delete socket;
	  return (true);
	}
      sets[0] = ALinuxSocket::functorType(*this, &Server::tcpAuthRecv);
      socket->setSets(sets);
      list.push_back(socket);
    }
  return (true);
}

bool			Server::tcpAuthRecv(ClientListType & list,
					    ClientListType::iterator & it)
{
  creation::Socket::setsType		sets(3, NULL);
  std::string				str;
  buffer::Buffer			buff;
  Protocol::Packet			*packet;

  while ((*it)->recv(str, buff.getSingleSize()) > 0)
    buff.push(str);
  if ((packet = getNextPacket(buff)) != NULL
      && (packet->getHeader().getInstruction() == 0x0001))
  {
    sets[1] = ALinuxSocket::functorType(*this, &Server::tcpAuthSend);
    (*it)->setSets(sets);
    delete packet;
  }
  else
  {
    delete *it;
    --(it = list.erase(it));
  }
  return (true);
}

bool			Server::tcpAuthSend(ClientListType & list,
					    ClientListType::iterator & it)
{
  creation::Socket::setsType		sets(3, NULL);
  Protocol::Packet			*packet;
  std::string				to_send, test;

  (_ClientMap[(*it)->getFd()] = new Client(_roomManager))->setRoomManager(_roomManager);
  packet = PacketFactory::createAuthPacket((*it)->getFd());
  (*it)->send(Protocol::Serialize::stringalize(*packet, to_send));
  sets[0] = ALinuxSocket::functorType(*this, &Server::tcpRecvManager);
  sets[1] = ALinuxSocket::functorType(*this, &Server::commonSendManager);
  (*it)->setSets(sets);
  delete packet;
  return (true);
}

bool			Server::commonRecvManager(creation::Socket::listType &list,
						  creation::Socket::retFunType &it)
{
  std::string			str;
  Protocol::Packet		*packet;
  buffer::Buffer		buff;
  ClientMapType::iterator	mapIt;

  while ((*it)->recv(str, buff.getSingleSize()) > 0)
    buff.push(str);
  while ((packet = getNextPacket(buff)) != NULL)
    if ((mapIt = _ClientMap.find(packet->getHeader().getMagic())) != _ClientMap.end())
      mapIt->second->pushPacketIn(packet);
  return (true);
}

bool			Server::commonSendManager(creation::Socket::listType &list,
						  creation::Socket::retFunType &it)
{
  std::string		to_send;
  Protocol::Packet	*packet;
  network::Client	*clt(_ClientMap[(*it)->getFd()]);

  while ((packet = clt->popPacketOut()) != NULL)
  {
    (*it)->send(Protocol::Serialize::stringalize(*packet, to_send));
    delete packet;
  }
  return (true);
}

bool			Server::tcpRecvManager(ClientListType & list, ClientListType::iterator & it)
{
  std::string	str;

  if ((*it)->recv(str, 1000) <= 0)
    {
      _ClientMap.erase((*it)->getFd());
      delete (*it);
      --(it = list.erase(it));
      return (true);
    }
  return(commonRecvManager(list, it));
}
