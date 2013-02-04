//
// Server.cpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/Server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan 16 22:31:08 2013 luca savarino
// Last update Sun Feb  3 22:41:50 2013 luca savarino
//

#include "LinuxMultiplexer.hpp"
#include "Server.hpp"

#include <functional>
#include <iostream>

using namespace network;

Server::Server(int tcpEntryPoint,
	       int udpEntryPoint,
	       unsigned int maxClientNbr)
  : _tcpEntryPoint(tcpEntryPoint),
    _udpEntryPoint(udpEntryPoint),
    _maxClientNbr((maxClientNbr <= (INT_MAX - 3)) ?
		  maxClientNbr : (INT_MAX - 3))
{
  SocketType::setsType		sets(3, NULL);
  SocketTCPType			*tcpServer;
  SocketUDPType			*udpServer;

  sets[0] = SocketType::functorType(*this,
				      &Server::connectionManager);
  (tcpServer = new SocketTCPType(sets))->bind(tcpEntryPoint);
  sets[0] = SocketType::functorType(*this,
  				      &Server::commonRecvManager);
  (udpServer = new SocketUDPType(sets))->bind(udpEntryPoint);
  _clientList.push_back(tcpServer);
  _clientList.push_back(udpServer);
}

Server::Server(Server const& to_copy)
  : _tcpEntryPoint(to_copy._tcpEntryPoint),
    _udpEntryPoint(to_copy._udpEntryPoint),
    _clientList(to_copy._clientList),
    _clientMap(to_copy._clientMap),
    _maxClientNbr(to_copy._maxClientNbr)
{}

Server	&	Server::operator=(Server const& to_copy)
{
  _tcpEntryPoint = to_copy._tcpEntryPoint;
  _udpEntryPoint = to_copy._udpEntryPoint;
  _clientList = to_copy._clientList;
  _clientMap = to_copy._clientMap;
  _maxClientNbr = to_copy._maxClientNbr;

  return (*this);
}

Server::~Server()
{
  ClientListType::iterator	it;

  for(it = _clientList.begin(); it != _clientList.end(); ++it)
    delete *it;
}

// void		Server::setRoomManager(manageroom::IObserver *roomManager)
// {
//   _roomManager = roomManager;
// }

bool			Server::start()
{
  return(network::LinuxMultiplexer::start(_clientList,
					  network::LinuxMultiplexer::callbackType(NULL)));
}

bool			Server::connectionManager(ClientListType & list,
						  ClientListType::iterator & it)
{
  SocketType::setsType		sets(3, NULL);
  SocketType			*socket;
  //Client				*client;

  std::cout << "new client" << std::endl;
  if ((socket = static_cast<network::LinuxSocketTCP *>(*it)->accept()) != NULL)
    {
      if (list.size() == _maxClientNbr
	  /*|| (client = new Client) != NULL*/)
	{
	  delete socket;
	  return (true);
	}
      //_clientMap[socket] = client;
      //sets[0] = Bind::bind(&Server::commonRecvManager);
      sets[0] = ALinuxSocket::functorType(*this, &Server::commonRecvManager);
      socket->setSets(sets);
      list.push_back(socket);
    }
  return (true);
}

bool			Server::commonRecvManager(creation::Socket::listType &,
						  creation::Socket::retFunType &it)
{
  std::string			str;
  ClientMapType::iterator	mapIt;

  while((*it)->recv(str,10) > 0)
    write(1, str.c_str(), str.size());
  // while ((*it)->recv(str, buff.getSingleSize()) > 0)
  //   buff.push(str);
  // while ((packet = getNextPacket(buff)) != NULL)
  //   if ((mapIt = _ClientMap.find(packet->getHeader().getMagic())) != _ClientMap.end())
  //     mapIt->second->pushPacketIn(packet);
  return (true);
}

// bool			Server::commonSendManager(creation::Socket::listType &list,
// 						  creation::Socket::retFunType &it)
// {
//   std::string		to_send;
//   Protocol::Packet	*packet;
//   network::Client	*clt(_ClientMap[(*it)->getFd()]);

//   while ((packet = clt->popPacketOut()) != NULL)
//   {
//     (*it)->send(Protocol::Serialize::stringalize(*packet, to_send));
//     delete packet;
//   }
//   return (true);
// }

// bool			Server::tcpRecvManager(ClientListType & list, ClientListType::iterator & it)
// {
//   std::string	str;

//   if ((*it)->recv(str, 1000) <= 0)
//     {
//       _ClientMap.erase((*it)->getFd());
//       delete (*it);
//       --(it = list.erase(it));
//       return (true);
//     }
//   return(commonRecvManager(list, it));
// }
