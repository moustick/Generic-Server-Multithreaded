//
// WinCondVar.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory/WinCondVar
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:43:56 2012 luca savarino
// Last update Wed Dec 19 17:43:57 2012 luca savarino
//

#include "WinCondVar.hpp"

using namespace condvar;

WinCondVar::WinCondVar()
{
  InitializeConditionVariable(&_condVar);
  _mutex = CreateMutex(NULL, false, NULL);
  _created = true;
}

WinCondVar::~WinCondVar()
{

}

void	WinCondVar::wait()
{
  if (!_created)
    return;
  
}

void	WinCondVar::destroy_cond()
{
  if (!_created)
    return ;
}

void	WinCondVar::destroy_mutex()
{
  if (!_created)
    return ;

}

void	WinCondVar::destroy_both()
{
  if (!_created)
    return ;
  
}
