//
// main.cpp for  in /home/cottin_j//Desktop
// 
// Made by joffrey cottin
// Login   <cottin_j@epitech.net>
// 
// Started on  Fri Dec 28 23:26:09 2012 joffrey cottin
// Last update Sun Jan 20 19:45:22 2013 luca savarino
//

#include "Server.hpp"

int main(int ac, char** av)
{
  network::Server	serv(12346, 12347);
  
  serv.start();
}
