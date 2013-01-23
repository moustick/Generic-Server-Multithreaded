//
// WinThread.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:52:31 2012 luca savarino
// Last update Wed Dec 19 17:52:35 2012 luca savarino
//

#include "pthread.h"
#include "WinThread.hpp"

using namespace thread;

inline void		WinThread::start_thread()
{
  pthread_create(static_cast<pthread_t *>(_thread), NULL, &_jumper, this);
}

WinThread::WinThread();

WinThread::WinThread(WinThread const& to_copy)
  : AThread(to_copy), _thread(new pthread_t)
{
  start_thread();
}

WinThread::WinThread(WinThread ptr)
  : AThread(ptr)
{
  start_thread();
}

WinThread::~WinThread()
{
  pthread_cancel(*(static_cast<pthread_t *>(_thread)));
  delete _thread;
}

void	WinThread::waitforend()
{
  pthread_join(*(static_cast<pthread_t *>_thread), NULL);
}
