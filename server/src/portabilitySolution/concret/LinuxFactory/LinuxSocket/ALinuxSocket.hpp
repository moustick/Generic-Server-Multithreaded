//
// ALinuxSocket.hpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 01:25:49 2013 luca savarino
// Last update Mon Jan 28 15:27:53 2013 luca savarino
//

#ifndef	ALINUXSOCKET__
# define	ALINUXSOCKET__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <list>
#include <string>
#include <vector>

#include "Functor_2.hpp"
#include "ISocket.hpp"

namespace network
{
  class ALinuxSocket : public ISocket
  {
  public :
    typedef	std::list<ALinuxSocket *>		listType;
    typedef	listType::iterator			retFunType;
    typedef	functor::Functor<bool (listType &,
    				       retFunType &)>	functorType;
    typedef	std::vector<functorType>		setsType;

  protected :
    typedef	bool	(*ptr)(ALinuxSocket &, addrinfo &);


  protected :
    addrinfo	_hints;
    int		_fd;

  private :
    setsType	_sets;

  protected :
    bool	getaddrinfo(std::string const&,
			    std::string const&,
			    ptr, std::string const&, addrinfo &);

  public :
    ALinuxSocket();
    ALinuxSocket(ALinuxSocket const&);
    ALinuxSocket(setsType const&, int fd = -1);
    virtual	~ALinuxSocket();

    ALinuxSocket	&	operator=(ALinuxSocket const&);

    void			setSets(setsType & sets);
    setsType		const&	getSets()		const;
    int				getFd()			const;

    virtual void		initAddrinfo();

    virtual bool		bind(int, std::string const&, int)	= 0;
    virtual bool		connect(int, std::string const&)	= 0;
    virtual int			recv(std::string &, int)		= 0;
    virtual int			send(std::string const&)		= 0;
  };
}

#endif
