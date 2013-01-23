//
// main.cpp for rtype in /home/savari_l//tech_3/cpp/test_reseau
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan  9 16:01:46 2013 luca savarino
// Last update Sun Jan 20 19:39:23 2013 luca savarino
//

#include <iostream>

#include "AFactory.hpp"

int					main()
{
  creation::SocketTCP			tcpClient;
  creation::SocketUDP			udpClient;
  
  tcpClient.connect(12346, "127.0.0.1");
  udpClient.connect(12347, "127.0.0.1");
  tcpClient.send("Je suis le client TCP");
  udpClient.send("Je suis le client UDP");
  return (0);
}
