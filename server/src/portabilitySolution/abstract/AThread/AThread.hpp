//
// AThread.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/AThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:59:28 2012 luca savarino
// Last update Wed Dec 19 17:55:03 2012 luca savarino
//

#ifndef	ATHREAD__
# define	ATHREAD__

namespace thread
{
  class	AThread
  {
  public :
    typedef	void *(*ptr)(void *);

  protected :
    ptr		_jumper;

  public :
    AThread();
    AThread(ptr const&);
    AThread(AThread const&);
    virtual ~AThread();

    virtual void	waitForEnd() = 0;
  };
}

#endif
