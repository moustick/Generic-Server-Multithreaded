//
// RoomManager.cpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 19:15:31 2012 cybil bourely
// Last update Sun Jan 27 19:21:29 2013 luca savarino
//

#include <string>
#include <iostream>

#include "ARoom.hpp"
#include "RoomManager.hpp"

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
