//
// LinuxMultiplexer.hpp for rtype in /home/savari_l//tech_3/cpp/test_reseau/test_tcp/server
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 01:25:49 2013 luca savarino
// Last update Mon Jan 28 17:43:10 2013 luca savarino
//

#ifndef	LINUXMULTIPLEXER__
# define	LINUXMULTIPLEXER__

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include <list>
#include <vector>

#include "Functor_2.hpp"

namespace network
{
  class ALinuxSocket;

  class LinuxMultiplexer
  {
  public :
    typedef	functor::Functor<void ()>		callbackType;
    typedef	std::list<ALinuxSocket *>		listType;
    typedef	listType::iterator			retFunType;
    typedef	functor::Functor<bool (listType &,
				       retFunType &)>	functorType;
    typedef	std::vector<functorType>		setsType;

  private :
    static bool	testSets(setsType const&);
    static int	getMaxFd(listType &);
    static int	initSets(listType const&,
			 std::vector<fd_set> &);

  public :
    LinuxMultiplexer();
    LinuxMultiplexer(LinuxMultiplexer const&);
    LinuxMultiplexer(setsType const&, int fd = -1);
    ~LinuxMultiplexer();

    static	bool		start(listType	&, callbackType const&);
    
    LinuxMultiplexer	&	operator=(LinuxMultiplexer const&);
  };
}

#endif
