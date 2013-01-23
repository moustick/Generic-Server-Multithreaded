//
// ISocket.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/ISocket
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:58:56 2012 luca savarino
// Last update Wed Jan 16 19:08:34 2013 luca savarino
//

#ifndef	ISOCKET__
# define	ISOCKET__

#include <string>

namespace network
{
  class	ISocket
  {
  public :
    virtual	~ISocket(){}

    virtual bool		bind(int, std::string const&, int)	= 0;
    virtual bool		connect(int, std::string const&)	= 0;
    virtual int			recv(std::string &, int)		= 0;
    virtual int			send(std::string const&)		= 0;
  };
}

#endif
