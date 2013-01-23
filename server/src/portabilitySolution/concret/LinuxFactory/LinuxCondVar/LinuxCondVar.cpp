//
// LinuxCondVar.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/LinuxFactory/LinuxCondVar
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 16:39:10 2012 luca savarino
// Last update Wed Jan 16 12:58:52 2013 luca savarino
//

#include "LinuxCondVar.hpp"

using namespace condvar;

LinuxCondVar::LinuxCondVar()
  :_condVar(condVarType::fctType(*this, static_cast<void(LinuxCondVar::*)()>(NULL))
				 , new pthread_cond_t),
   _mutex(mutexType::fctType(*this, static_cast<void(LinuxCondVar::*)()>(NULL))
			     , new pthread_mutex_t),
   _created(true)
{
  if (pthread_cond_init(_condVar.getPointer(), NULL))
    {
      destroy_both();
      _created =  false;
    }
  else if (pthread_mutex_init(_mutex.getPointer(), NULL))
    {
      _condVar.setFct(condVarType::fctType(*this, &LinuxCondVar::destroy_cond));
      destroy_both();
      _created = false;
    }
  else
    {
      _condVar.setFct(condVarType::fctType(*this, &LinuxCondVar::destroy_cond));
      _mutex.setFct(mutexType::fctType(*this, &LinuxCondVar::destroy_mutex));
    }
}

LinuxCondVar::LinuxCondVar(LinuxCondVar const& to_copy)
  : _condVar(to_copy._condVar), _mutex(to_copy._mutex)
{}

LinuxCondVar::~LinuxCondVar()
{}

void	LinuxCondVar::wait()
{
  if (!_created)
    return ;
  pthread_mutex_lock(_mutex.getPointer());
  pthread_cond_wait(_condVar.getPointer(), _mutex.getPointer());
  pthread_mutex_unlock(_mutex.getPointer());
}

void	LinuxCondVar::signal()
{
  if (!_created)
    return ;
  pthread_cond_signal(_condVar.getPointer());
}

void	LinuxCondVar::broadcast()
{
  if (!_created)
    return ;
  pthread_cond_broadcast(_condVar.getPointer());
}

void	LinuxCondVar::destroy_cond()
{
   if (!_created)
     return ;
   pthread_cond_destroy(_condVar.getPointer());
}

void	LinuxCondVar::destroy_mutex()
{
  if (!_created)
    return ;
  pthread_mutex_destroy(_mutex.getPointer());
}

void	LinuxCondVar::destroy_both()
{
  if (!_created)
    return ;
  _condVar.destroy();
  _mutex.destroy();
  _created = false;
}

LinuxCondVar &	LinuxCondVar::operator=(LinuxCondVar const& to_copy)
{
  _condVar = to_copy._condVar; 
  _mutex = to_copy._mutex;

  return (*this);
}
