//
// Server.hpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/Server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Jan 16 22:30:57 2013 luca savarino
// Last update Sun Feb  3 19:37:54 2013 luca savarino
//

#ifndef	SERVER__
# define	SERVER__

#include <climits>
#include <map>

#include "AFactory.hpp"

// namespace manageroom
// {
//   class	IObserver;
// }

namespace  network
{
  class Client;
  class Server
  {
    typedef	creation::SocketUDP		SocketUDPType;
    typedef	creation::SocketTCP		SocketTCPType;
    typedef	creation::Socket		SocketType;
    typedef	std::list<SocketType *>		ClientListType;
    typedef	std::map<SocketType *, Client*>	ClientMapType;

  private :
    int				_tcpEntryPoint;
    int				_udpEntryPoint;
    ClientListType		_clientList;
    ClientMapType		_clientMap;
    unsigned int		_maxClientNbr;
    //manageroom::IObserver *	_roomManager;

  private :
    bool			connectionManager(ClientListType & list,
						  ClientListType::iterator & it);
    // void			setRoomManager(manageroom::IObserver *roomManager);
    bool			commonRecvManager(ClientListType &list,
    						  creation::Socket::retFunType &it);
    // bool			commonSendManager(ClientListType &list,
    // 						  creation::Socket::retFunType &it);
    // bool			tcpRecvManager(ClientListType & list, ClientListType::iterator & it);

  public :
    Server(int		tcpEntryPoint	= 7777,
	   int		udpEntryPoint	= 6666,
	   unsigned int	maxClientNbr	= INT_MAX - 3);
    Server(Server const&);
    ~Server();

    Server	&	operator=(Server const&);

    bool		start();
  };
}

#endif
