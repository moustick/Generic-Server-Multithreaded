//
// ICondvar.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/ICondvar
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:55:59 2012 luca savarino
// Last update Wed Dec 19 17:54:05 2012 luca savarino
//

#ifndef	ICONDVAR__
# define	ICONDVAR__

namespace condvar
{
  class	ICondVar
  {
  public :
    virtual	~ICondVar(){}

    virtual	void	wait() = 0;
    virtual	void	signal() = 0;
    virtual	void	broadcast() = 0;
  };
}

#endif
