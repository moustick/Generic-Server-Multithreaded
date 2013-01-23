//
// Server.hpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/Server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan 16 22:30:57 2013 luca savarino
// Last update Sun Jan 20 19:07:11 2013 luca savarino
//

#ifndef	SERVER__
# define	SERVER__

#include <climits>
#include <map>

#include "AFactory.hpp"

namespace buffer
{
  struct Buffer;
}

namespace Protocol
{
  struct Packet;
}

namespace manageroom
{
  class	IObserver;
}

namespace  network
{
  class Client;
  class Server
  {
    typedef	std::pair<int, Client*>		ClientPairType;
    typedef	std::map<int, Client*>		ClientMapType;
    typedef	creation::Socket::listType	ClientListType;

  private :
    int				_tcpEntryPoint;
    int				_udpEntryPoint;
    ClientMapType		_ClientMap;
    ClientListType		_ClientList;
    int				_maxClientNbr;
    manageroom::IObserver *	_roomManager;

  private :
    bool			tcpConnectionManager(ClientListType & list,
						     ClientListType::iterator & it);
    Protocol::Packet	*	getNextPacket(buffer::Buffer &buff) const;
    void			setRoomManager(manageroom::IObserver *roomManager);
    bool			tcpAuthRecv(ClientListType &, ClientListType::iterator &);
    bool			tcpAuthSend(ClientListType & list, ClientListType::iterator &);
    bool			commonRecvManager(ClientListType &list,
						  creation::Socket::retFunType &it);
    bool			commonSendManager(ClientListType &list,
						  creation::Socket::retFunType &it);
    bool			tcpRecvManager(ClientListType & list, ClientListType::iterator & it);

  public :
    Server(int	tcpEntryPoint	= 7777,
	   int	udpEntryPoint	= 6666,
	   int	maxClientNbr	= INT_MAX - 3);
    Server(Server const&);
    ~Server();

    Server	&	operator=(Server const&);

    bool		start();
  };
}

#endif
