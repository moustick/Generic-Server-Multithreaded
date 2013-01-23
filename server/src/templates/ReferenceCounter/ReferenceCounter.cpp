//
// ReferenceCounter.hpp for R-Type in /home/savari_l//tech_3/cpp/R-Type/ReferenceCounters
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Sat Dec 22 16:47:27 2012 luca savarino
// Last update Sun Dec 23 03:32:55 2012 luca savarino
//

#include "ReferenceCounter.hpp"

using namespace smartpointer;

ReferenceCounter::ReferenceCounter()
  : _value(1)
{}

ReferenceCounter::ReferenceCounter(ReferenceCounter const& to_copy)
  : _value(to_copy._value)
{}

ReferenceCounter::~ReferenceCounter()
{}

ReferenceCounter	&	ReferenceCounter::operator=(ReferenceCounter const& to_copy)
{
  _value = to_copy._value;
  return (*this);
}

ReferenceCounter	&	ReferenceCounter::operator++()
{
  ++_value;
  return (*this);
}

ReferenceCounter	&	ReferenceCounter::operator++(int)
{
  _value++;
  return (*this);
}

ReferenceCounter	&	ReferenceCounter::operator--()
{
  --_value;
  return (*this);
}

ReferenceCounter	&	ReferenceCounter::operator--(int)
{
  _value--;
  return (*this);
}

int				ReferenceCounter::getValue()		const
{
  return (_value);
}
