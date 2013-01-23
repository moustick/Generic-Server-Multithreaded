#ifndef THREADCPP__
# define	THREADCPP__

#include "AFactory.hpp"
#include "Functor.hpp"
#include "SharedPointer.hpp"

namespace thread
{
  template <typename T>
  class	ThreadCpp
  {
  protected :
    static void	*	jumper(void *ptr);

  public :
    enum		eState{RUNNING, STOPPED};
    
  private :
    functor::Functor<T>	_functor;
    eState		_state;
    bool		_start;
    creation::Mutex	_startMutex;
    creation::CondVar	_condVar, _endCondVar, _commonEndCondVar;
    creation::Thread	_thread;
    
  private :
    void	startSynchronize();

  public :
    ThreadCpp();
    ThreadCpp(ThreadCpp<T> const&);
    ThreadCpp(functor::Functor<T> const&);
    ~ThreadCpp();

    ThreadCpp<T>	&	operator=(ThreadCpp<T> const&);
    ThreadCpp<T>	&	operator=(functor::Functor<T> const&);

    bool		IsRunning();
    void		run();
    void		waitForCommonEnd();
    void		waitForEnd();
  };

  template <class T>
  ThreadCpp<T>::ThreadCpp()
    :	_state(STOPPED),
	_start(false),
	_thread(jumper, this)
  {
    startSynchronize();
  }

  template <class T>
  ThreadCpp<T>::ThreadCpp(ThreadCpp<T> const& to_copy)
    : _functor(to_copy._functor),
      _state(STOPPED),
      _start(false),
      _commonEndCondVar(to_copy._commonEndCondVar),
      _thread(jumper, this)
  {
    startSynchronize();
  }

  template <class T>
  ThreadCpp<T>::ThreadCpp(functor::Functor<T> const& functor)
    :	_functor(functor),
	_state(STOPPED),
	_start(false),
	_thread(jumper, this)
  {
    startSynchronize();
  }

  template <class T>
  ThreadCpp<T>::~ThreadCpp(){}

  template <class T>
  ThreadCpp<T>	&	ThreadCpp<T>::operator=(ThreadCpp<T> const& to_copy)
  {
    waitForEnd();
    _commonEndCondVar = to_copy._commonEndCondVar;
    _functor = to_copy._functor;
    return (*this);
  }

  template <class T>
  ThreadCpp<T>	&	ThreadCpp<T>::operator=(functor::Functor<T> const& to_copy)
  {
    waitForEnd();
    _functor = to_copy;
    return (*this);
  }

  template <class T>
  void		*	ThreadCpp<T>::jumper(void *ptr)
  {
    ThreadCpp<T> *	threadCpp = static_cast<ThreadCpp<T> *>(ptr);
      
    threadCpp->_startMutex.lock();
    threadCpp->_start = true;
    threadCpp->_startMutex.unlock();
    do
      {
	threadCpp->_condVar.wait();
	if (threadCpp->_state == RUNNING
	    && threadCpp->_functor.isCallable())
	  {
	    (threadCpp->_functor)();
	    threadCpp->_state = STOPPED;
	    threadCpp->_endCondVar.signal();
	    threadCpp->_commonEndCondVar.broadcast();
	  }
      } while (true);
    return (NULL);
  }

  template <class T>
  bool			ThreadCpp<T>::IsRunning()
  {
    return (_state == RUNNING);
  }
  
  template <class T>
  void			ThreadCpp<T>::run()
  {
    _state = RUNNING;
    _condVar.signal();
  }
  
  template <class T>
  void			ThreadCpp<T>::startSynchronize()
  {
    while (true)
      if (_startMutex.trylock())
	{
	  if (_start)
	    {
	      _startMutex.unlock();
	      return;
	    }
	  _startMutex.unlock();
	}
  }

  template <class T>
  void			ThreadCpp<T>::waitForEnd()
  {
    if (_state == RUNNING)
      _endCondVar.wait();
  }
  
  template <class T>
  void			ThreadCpp<T>::waitForCommonEnd()
  {
    _commonEndCondVar.wait();
  }
}

#endif
