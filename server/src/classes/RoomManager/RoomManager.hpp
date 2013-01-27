//
// RoomManager.hpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 18:25:55 2012 cybil bourely
// Last update Sun Jan 27 19:22:40 2013 luca savarino
//

#ifndef		ROOMMANAGER_HPP__
# define	ROOMMANAGER_HPP__

#include <list>
#include <map>

#include "ARoom.hpp"
#include "Client.hpp"
#include "IObserver.hpp"
#include "ThreadPool.hpp"

namespace manageroom
{
  class RoomManager : public IObserver
  {
  public:
    typedef	std::list<ARoom *>						roomListType;
    typedef	threadpool::ThreadPool						threadPoolType;
    typedef	void (RoomManager::*pointerType)(clientType &);
    typedef	std::map<unsigned char, pointerType>				instrMapType;

  public :
    struct t_instr
    {
      char	instr;
      void	(RoomManager::*ptr)(network::Client *);
    };

  private:
    instrMapType			_instrMap;
    unsigned int			_nbThInCache;
    roomListType			_roomList;
    threadPoolType			_threadPool;
    bool				_isRunning;

  private :
    ARoom			*searchRoom(const std::string &);

  public :
    RoomManager(unsigned int);
    RoomManager(const RoomManager &);
    RoomManager();
    ~RoomManager() {}

    RoomManager			&operator=(const RoomManager &);

    void			cycle();
  };

}

#endif		// ROOMMANAGER_HPP__
