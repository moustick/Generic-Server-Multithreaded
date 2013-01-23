//
// WinMutex.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinMutex
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:45:12 2012 luca savarino
// Last update Wed Dec 19 17:45:27 2012 luca savarino
//

#include "WinMutex.hpp"

using namespace mutex;

WinMutex::WinMutex()
{
  InitializeCriticalSection(&CriticalSection);
  _mutex = CreateMutex(NULL, false, NULL);
  _created = true;
  if (_mutex == NULL)
    _created = false;
}

WinMutex::WinMutex(WinMutex const &cp) : _mutex(cp._mutex)
{
}

WinMutex::~WinMutex()
{
  DeleteCriticalSection(&CriticalSection);
}

void	WinMutex::destroy_mutex()
{
  if (!_created)
    return ;
  CloseHandle(_mutex);
}

void	WinMutex::lock()
{
  if (!_created)
    return ;
  EnterCriticalSection(&_mutex);
}

void	WinMutex::unlock()
{
  if (!_created)
    return ;
  LeaveCriticalSection(&_mutex);
}

BOOL	WinMutex::trylock()
{
  if (!_created)
    return ;
  return (TryEnterCriticalSection(&_mutex));
}
