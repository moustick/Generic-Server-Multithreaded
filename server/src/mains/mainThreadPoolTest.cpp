//
// main.cpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/ThreadPool
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Thu Dec 20 16:46:18 2012 luca savarino
// Last update Wed Jan 16 13:29:45 2013 luca savarino
//

#include <iostream>

#include <unistd.h>

#include "ThreadPool.hpp"

class	t1
{
  unsigned int	_time;

public :
  t1(unsigned int time = 10)
    : _time(time)
  {}
  ~t1(){}

  void	operator()()
  {
    std::cout << "start task" << std::endl;
    sleep(_time);
    std::cout << "end of task" << std::endl;
  }
  void  tata()
  {

  }
};

void	*j(void *)
{
  std::cout << "debut" << std::endl;
  sleep(4);
  return (NULL);
}

void	a()
{}

int main()
{
  threadpool::ThreadPool<void ()>	pool(50);
  t1	task(10), task2(3), task3(4), task4(2), task5(1);

  pool.pushTask(task, &t1::operator());
  pool.pushTask(task3);
  pool.pushTask(task4);
  pool.pushTask(task5);
  pool.pushTask(a);

  pool.waitForEnd();

  pool.pushTask(task2);
  pool.pushTask(task3);

  return (0);
}
