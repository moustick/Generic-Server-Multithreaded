//
// ThreadPool.cpp for rtype in /home/savari_l//tech_3/cpp/rtype-2015-cottin_j/src/RoomManager
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Mon Jan 14 05:31:32 2013 luca savarino
// Last update Sun Jan 20 15:19:21 2013 luca savarino
//

#include <ThreadPool.hpp>

using namespace threadpool;

ThreadPool::ThreadPool(unsigned int n)
  : _threads(n)
{
  for (; n; --n)
    _threads[n - 1] = new threadCppType();
}

ThreadPool::~ThreadPool()
{
  threadVectorType::iterator	it;

  waitForEnd();
}

void	ThreadPool::pushTask(taskType const& task)
{ 
  typename threadVectorType::iterator	it;

  for(it = _threads.begin(); it != _threads.end(); ++it)
    if(!(*it)->IsRunning())
      {
	(**it = task).run();
	return;
      }
  _taskQueue.push(task);
}

bool	ThreadPool::threadWorking()
{
  typename threadVectorType::iterator	it;

  for(it = _threads.begin(); it != _threads.end(); ++it)
    if((*it)->IsRunning())
      return (true);
  return (false);
}

void	ThreadPool::waitForEnd()
{
  typename threadVectorType::iterator	it;

  while(true)
    {
      if (threadWorking())
	(*(_threads.begin()))->waitForCommonEnd();
      if (!_taskQueue.size())
	break;
      pushTask(_taskQueue.front());
      _taskQueue.pop();
    }
  for(it = _threads.begin(); it != _threads.end(); ++it)
    (*it)->waitForEnd();
}
