//
// Client.hpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 18:14:07 2012 cybil bourely
// Last update Sun Jan 20 17:32:57 2013 luca savarino
//

#ifndef		CLIENT_HPP__
# define	CLIENT_HPP__

#include <string>
#include <queue>

#include "AFactory.hpp"

namespace manageroom
{
  class IObserver;
}

namespace Protocol
{
  struct Packet;
}

namespace network
{
  class Client
  {
  public :
    typedef	Protocol::Packet		packetType;
    typedef	std::queue<packetType *>	packetQueueType;

  private:
    packetQueueType		_msgQueueIn;
    packetQueueType		_msgQueueOut;
    manageroom::IObserver	*_roomManager;
    unsigned int		_id;
    Protocol::Packet		*_packet;
    std::string			_roomName;
    creation::Mutex		*_mutex;
    std::string			_res;
    creation::Socket::setsType	_sets;
    bool                                        _boolState;

  public:
    Client(manageroom::IObserver *);
    Client(const Client &);
    Client();
    ~Client();

    Client			&operator=(const Client &);

    bool                                          getBoolState();
    void                                          setBoolState();
    void			pushPacketIn(Protocol::Packet *);
    void			pushPacketOut(Protocol::Packet *);
    Protocol::Packet	*	popPacketIn();
    Protocol::Packet	*	popPacketOut();
    Protocol::Packet	*	frontPacketOut();
    Protocol::Packet	*	frontPacketIn();
    void			setRoomManager(manageroom::IObserver *);

    std::string		getRoomName() const;
    std::string		&getUserName() const;
    unsigned int		getId() const;

    void			setRoomName(const std::string &);
    void			setId(unsigned int);
  };
}

#endif		// CLIENT_HPP__
