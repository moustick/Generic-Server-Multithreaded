#ifndef BUFFER
#define BUFFER

#include <list>
#include <string>

//namespace std
//{
//  class string;
//}

namespace buffer {
	class Buffer {
	  char *createElem();

	  int			_allocSize;
	  int			_indexWrite;
	  int			_indexRead;
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
