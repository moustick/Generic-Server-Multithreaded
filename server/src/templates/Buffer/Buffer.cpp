#include <cstring>
#include <iostream>

#include "Buffer.hpp"

using namespace buffer;

char *Buffer::createElem()
{
  char *b = new char[_allocSize];
  memset(b, 0, sizeof(char) * _allocSize);
}

Buffer::Buffer(int allocSize)
  :_allocSize(allocSize), _indexWrite(0), _indexRead(0)
{
  _buffList.push_back(createElem());
  _iteList = _buffList.begin();
}

Buffer::~Buffer()
{
  delete [] _buffList.front();
}

unsigned int Buffer::getSingleSize() const
{
  return _allocSize;
}

std::string & Buffer::getPiece(std::string & buffer, int size)
{
  int	rest, restB = 0;
  int tmpRead = _indexRead;
  int tmpWrite = _indexWrite;

  if (_buffList.front() == _buffList.back() && tmpRead >= tmpWrite)
    {
      tmpRead = tmpWrite = 0;
      return buffer;
    }
  if ((rest = (size + tmpRead) - _allocSize) <= 0)
    {
      buffer.append(_buffList.front() + tmpRead, size);
      tmpRead += size;
    }
  else
    {
      buffer.append(_buffList.front() + tmpRead, _allocSize - tmpRead);
      char * b = _buffList.front();
      delete [] b;
      _buffList.pop_front();
      buffer.append(_buffList.front(), rest);
    }
  return buffer;
}

void Buffer::push(std::string & buffer)
{
  int	rest;
  
   if ((rest = _allocSize - (buffer.size() + _indexWrite)) >= 0)
    {
      memcpy(*_iteList + _indexWrite, buffer.c_str(), buffer.size());
      _indexWrite += buffer.size();
    }
  else
    {
      _buffList.push_back(createElem());
      memcpy(*_iteList + _indexWrite, buffer.c_str(), buffer.size() + rest);
      ++_iteList;
      memcpy(*_iteList, buffer.c_str() + (buffer.size() + rest), _indexWrite = -rest);
    }
   std::cout << *_iteList << " -- "<<buffer <<std::endl;;
}

std::string & Buffer::pop(std::string & buffer, int size)
{
  int	rest, restB = 0;

  if (_buffList.front() == _buffList.back() && _indexRead >= _indexWrite)
    {
      _indexRead = _indexWrite = 0;
      return buffer;
    }
  if ((rest = (size + _indexRead) - _allocSize) <= 0)
    {
      buffer.append(_buffList.front() + _indexRead, size);
      _indexRead += size;
    }
  else
    {
      buffer.append(_buffList.front() + _indexRead, _allocSize - _indexRead);
      char * b = _buffList.front();
      delete [] b;
      _buffList.pop_front();
      buffer.append(_buffList.front(), rest);
    }
  return buffer;
}
