//
// IObserver.hpp for  in /home/bourel_c//Tech3/R-Type/serveur
// 
// Made by cybil bourely
// Login   <bourel_c@epitech.net>
// 
// Started on  Wed Dec 19 18:11:13 2012 cybil bourely
// Last update Sun Jan 20 21:45:04 2013 luca savarino
//

#ifndef		IOBSERVER_HPP__
# define	IOBSERVER_HPP__

#include "Client.hpp"

namespace manageroom
{
  class IObserver
  {
  public :
    typedef	network::Client							clientType;

  public:
    virtual void		notify(clientType &)	= 0;
    virtual void		cycle()			= 0;
  };
}

#endif		// IOBSERVER_HPP__
