//
// LinuxMutex.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxMutex
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:00:38 2012 luca savarino
// Last update Wed Jan 16 12:57:21 2013 luca savarino
//

#include "LinuxMutex.hpp"

using namespace mutex;

LinuxMutex::LinuxMutex()
  : _mutex(mutexType::fctType(*this, static_cast<void(LinuxMutex::*)()>(NULL))
	   , new pthread_mutex_t),
    _created(false)
{
  if (pthread_mutex_init(_mutex.getPointer(), NULL))
    _mutex.destroy();
  else if ((_created = true))
    _mutex.setFct(mutexType::fctType(*this, &LinuxMutex::destroy_mutex));
}

LinuxMutex::LinuxMutex(LinuxMutex const& to_copy)
  : _mutex(to_copy._mutex)
{}

LinuxMutex::~LinuxMutex()
{}

void	LinuxMutex::lock()
{
  if (!_created)
    return;
  pthread_mutex_lock(_mutex.getPointer());
}

void	LinuxMutex::unlock()
{
  if (!_created)
    return;
  pthread_mutex_unlock(_mutex.getPointer());
}

bool	LinuxMutex::trylock()
{
  if (!_created)
    return false;
  return (!pthread_mutex_trylock(_mutex.getPointer()));
}

void	LinuxMutex::destroy_mutex()
{
  if (!_created)
    return;
  pthread_mutex_destroy(_mutex.getPointer());
}
