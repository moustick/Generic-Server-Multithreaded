//
// AThread.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/abstract/AThread
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Wed Dec 19 17:52:11 2012 luca savarino
// Last update Wed Dec 19 17:52:24 2012 luca savarino
//

#include <cstdlib>

#include "AThread.hpp"

using namespace thread;

AThread::AThread()
  : _jumper(NULL)
{}

AThread::AThread(ptr const& jumper)
  : _jumper(jumper)
{}

AThread::AThread(AThread const& to_copy)
  : _jumper(to_copy._jumper)
{}

AThread::~AThread()
{}
