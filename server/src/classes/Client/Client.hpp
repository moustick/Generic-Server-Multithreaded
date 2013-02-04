//
// Client.hpp for rtype in /home/savari_l//tech3/cpp/Generic-Server-Multithreaded/server/src
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Tue Jan 29 16:23:02 2013 luca savarino
// Last update Tue Jan 29 19:11:49 2013 luca savarino
//

#ifndef		CLIENT_HPP__
# define	CLIENT_HPP__

#include "AFactory.hpp"
#include <string>

namespace buffer
{
  class Buffer;
}

namespace network
{
  class Client
  {
  private:
    buffer::Buffer		_toSend;
    buffer::Buffer		_Receved;

  public:
    Client();
    Client(Client const&);
    ~Client();

    Client		&	Client::operator=(Client const&);

    void			send(std::string const&);
    std::string	&	recv(std::string &);
  };
}

#endif		// CLIENT_HPP__
