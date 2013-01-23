//
// ThreadPool.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/ThreadPool
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Thu Dec 20 15:04:56 2012 luca savarino
// Last update Sun Jan 20 15:18:52 2013 luca savarino
//

#ifndef	THREADPOOL__
# define THREADPOOL__

#include <queue>
#include <vector>

#include "Functor.hpp"
#include "ThreadCpp.hpp"

namespace	threadpool
{
  class ThreadPool
  {
    typedef	typename thread::ThreadCpp<void()>		threadCppType;
    typedef	typename std::vector<threadCppType *>		threadVectorType;
    typedef	typename functor::Functor<void()>	taskType;
    typedef	typename std::queue<taskType>		taskQueueType;

    threadVectorType				_threads;
    taskQueueType				_taskQueue;
    
  private :
    bool	threadWorking();

  public :
    ThreadPool(unsigned int);
    ~ThreadPool();
    
    void	pushTask(taskType const&);
    template<typename U, typename X>
    void	pushTask(X & object, U (X::* fct)() = &X::operator());
    void	waitForEnd();
  };
    
  template<typename U, typename X>
  void	ThreadPool::pushTask(X & object, U (X::* fct)())
  {pushTask(taskType(object, fct));}
}

#endif
