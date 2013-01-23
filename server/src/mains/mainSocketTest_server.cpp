//
// main.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan  9 16:01:46 2013 luca savarino
// Last update Wed Jan 16 17:58:20 2013 luca savarino
//

#include <iostream>

#include "AFactory.hpp"

bool					tcpClientReadManager(creation::Socket::listType   & liste,
							     creation::Socket::retFunType & it)
{
  creation::Socket			*client;
  std::string				str;

  if ((*it)->recv(str, 100) <= 0)
    {
      std::cout << "connection closed by TCP client" << std::endl;
      client = *it;
      it = liste.erase(it);
      delete client;
      return (true);
    }
  std::cout << "TCP client sent :" << str << std::endl;
  return (true);
}

bool					tcpServerManager(creation::Socket::listType   & liste,
							 creation::Socket::retFunType & it)
{
  creation::Socket::setsType		sets(3, NULL);
  creation::Socket			*client;

  if ((client = static_cast<network::LinuxSocketTCP *>(*it)->accept()) != NULL)
    {
      std::cout << "New TCP client connected" << std::endl;
      liste.push_back(client);
      sets[0] = tcpClientReadManager;
      client->setSets(sets);
    }
  return (true);
}

bool					udpServerManager(creation::Socket::listType   & liste,
							 creation::Socket::retFunType & it)
{
  creation::Socket			*client;
  std::string				str;

  if ((*it)->recv(str, 100) <= 0)
    {
      std::cout << "connection closed by UDP client" << std::endl;
      client = *it;
      it = liste.erase(it);
      delete client;
      return (true);
    }
  std::cout << "UDP client sent :" << str << std::endl;
  return (true);
}

int					main()
{
  creation::Socket::listType		liste;
  creation::Socket::setsType		sets(3, NULL);
  creation::SocketTCP			tcpServer;
  creation::SocketUDP			udpServer;
  
  sets[0] = tcpServerManager;
  (tcpServer = sets).bind(12346);
  sets[0] = udpServerManager;
  (udpServer = sets).bind(12347);
  liste.push_back(&tcpServer);
  liste.push_back(&udpServer);
  creation::Socket::select(liste);
  return (0);
}
