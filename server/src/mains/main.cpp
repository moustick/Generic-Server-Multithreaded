//
// main.cpp for  in /home/cottin_j//Desktop
// 
// Made by joffrey cottin
// Login   <cottin_j@epitech.net>
// 
// Started on  Fri Dec 28 23:26:09 2012 joffrey cottin
// Last update Mon Jan 28 17:36:11 2013 luca savarino
//

#include "Server.hpp"

int main()
{
   network::Server	serv(12346, 12347);
  
   serv.start();
  return (0);
}
