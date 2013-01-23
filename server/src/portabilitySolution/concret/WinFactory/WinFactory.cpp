//
// WinFactory.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/concret/WinFactory
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 15:55:04 2012 luca savarino
// Last update Wed Jan 16 19:10:22 2013 luca savarino
//

#include "WinFactory.hpp"

using namespace creation::windowscreation;

WinFactory::WinFactory()
{}

WinFactory::~WinFactory()
{}

condvar::ICondVar	*	WinFactory::createCondVar()
{
  return (new condvar::WinCondVar);
}

mutex::IMutex		*	WinFactory::createMutex()
{
  return (new mutex::WinMutex);
}

socket::ISocket		*	WinFactory::createSocket()
{
  return (new socket::WinSocket);
}

thread::IThread		*	WinFactory::createThread()
{
  return (new thread::WinThread);
}
