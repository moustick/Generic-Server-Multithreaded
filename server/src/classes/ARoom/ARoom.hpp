//
// ARoom.hpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 18:33:23 2012 cybil bourely
// Last update Sun Jan 20 16:40:42 2013 luca savarino
//

#ifndef		AROOM_HPP__
# define	AROOM_HPP__

#include <list>
#include <string>
#include <queue>
#include "Client.hpp"
#include "Functor.hpp"

namespace network
{
  class	Client;
}

namespace manageroom
{
  class ARoom
  {
  public:
    typedef	std::list<functor::Functor<void (void)> >	listTaskType;
    typedef	network::Client					clientType;
    typedef	std::list<clientType *>				clientListType;

  protected:
    // std::queue<const network::Client *>	_actionQueue;
    clientListType			_cltList;
    listTaskType			_taskList;
    unsigned int			_nbMaxPlayer;
    float				_timeout;

  private:
    bool				_launch;
    unsigned int			_rdyPlayer;
    std::string				_name;

  public :
    ARoom(const std::string &);
    ARoom(const ARoom &cpy);
    ARoom()
      : _timeout(0.0), _rdyPlayer(0)
    {}
    virtual ~ARoom() {}

    ARoom			&operator=(const ARoom &);

    void			deleteClient(clientType *);
    void			addClient(clientType *);

    const std::string		&getName() const;
    unsigned int                getNextId(); // const;
    const listTaskType		&getTaskList() const;
    float			getTimeOut() const;

    unsigned int		getNbMaxPlayer() const;
    unsigned int		getReadyPlayer() const;
    void			addRdyPlayer();

    void			setLaunch(bool);
  };
}

#endif		// AROOM_HPP__
