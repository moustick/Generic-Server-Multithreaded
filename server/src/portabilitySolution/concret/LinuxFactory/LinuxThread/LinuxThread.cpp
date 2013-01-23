//
// LinuxThread.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:52:31 2012 luca savarino
// Last update Wed Dec 19 17:52:35 2012 luca savarino
//

#include "pthread.h"
#include "LinuxThread.hpp"

using namespace thread;

void		LinuxThread::start_thread()
{
  _created = true;
  if (pthread_create(&(*static_cast<pthread_t *>(_thread)), NULL, _jumper, _instance) == 0)
    {
      _created = false;
      delete static_cast<pthread_t *>(_thread);
    }
}

LinuxThread::LinuxThread()
  : _thread(new pthread_t), _instance(NULL)
{}

LinuxThread::LinuxThread(LinuxThread const& to_copy)
  : AThread(to_copy), _thread(new pthread_t), _instance(to_copy._instance)
{
  start_thread();
}

LinuxThread::LinuxThread(ptr const& ptr, void *instance)
  : AThread(ptr), _thread(new pthread_t), _instance(instance)
{
  start_thread();
}

LinuxThread::~LinuxThread()
{
  if (!_created)
    return ;
  pthread_cancel(*(static_cast<pthread_t *>(_thread)));
  delete static_cast<pthread_t *>(_thread);
}

void	LinuxThread::waitForEnd()
{
  if (!_created)
    return ;
  pthread_join(*(static_cast<pthread_t *>(_thread)), NULL);
}

LinuxThread	&	LinuxThread::operator=(LinuxThread const& to_copy)
{
  if (!_created)
    return (*this);
  if (_jumper != NULL)
    pthread_cancel(*(static_cast<pthread_t *>(_thread)));
  _jumper = to_copy._jumper;
  _instance = to_copy._instance;
  start_thread();
  return (*this);
}
