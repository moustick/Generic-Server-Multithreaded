//
// IMutex.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/IMutex
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:58:20 2012 luca savarino
// Last update Wed Dec 19 17:54:31 2012 luca savarino
//

#ifndef	IMUTEX__
# define	IMUTEX__

namespace mutex
{
  class	IMutex
  {
  public :
    virtual	~IMutex(){}

    virtual	void	lock()		= 0;
    virtual	void	unlock()	= 0;
    virtual	bool	trylock()	= 0;
  };
}

#endif
