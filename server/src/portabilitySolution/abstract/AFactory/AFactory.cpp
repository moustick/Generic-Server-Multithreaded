#include "AFactory.hpp"

using namespace creation;

condvar::ICondVar	*	AFactory::getCondVar()
{
  return (new CondVar);
}

mutex::IMutex		*	AFactory::getMutex()
{
  return (new Mutex);
}

thread::AThread		*	AFactory::getThread()
{
  return (new 	  Thread);
}
