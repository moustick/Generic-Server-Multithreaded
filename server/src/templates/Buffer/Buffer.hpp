//
// Buffer.hpp for rtype in /home/savari_l//tech3/cpp/Generic-Server-Multithreaded/server/src
// 
// Made by luca savarino
// Login   <savari_l@epitech.net>
// 
// Started on  Tue Jan 29 16:35:20 2013 luca savarino
// Last update Tue Jan 29 16:35:21 2013 luca savarino
//

#ifndef BUFFER
#define BUFFER

#include <list>
#include <string>

namespace buffer {
	class Buffer {
	private :
	  char *createElem();

	private :
	  int				_allocSize;
	  int				_indexWrite;
	  int				_indexRead;
	  std::list<char*>		_buffList;
	  std::list<char*>::iterator	_iteList;

	public:
	  Buffer(int allocSize = 1024);
	  ~Buffer();

	  void push(std::string & buff);
	  std::string & pop(std::string &, int size);
	  std::string & getPiece(std::string & base, int size);
	  unsigned int getSingleSize() const;
	};
}

#endif //BUFFER
