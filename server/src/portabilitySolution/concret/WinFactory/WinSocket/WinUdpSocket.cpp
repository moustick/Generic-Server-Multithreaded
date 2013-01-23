
#include "WinUdpSock.hpp"

void		WinUdpSock::connect(void)
{
  if (WSAConnect(this->_sock,
		 static_cast<const sockaddr *>&(this->service),
		 sizeof(this->service),
		 NULL, NULL, NULL, NULL) == SOCKET_ERROR)
  {
    std::cerr << "/!\\ WSAConnect error. /!\\" << std::endl;
    closesocket(this->_sock);
  }
}

void		WinUdpSock::send(void *pack, int size)
{
  WSABUF	dataBuf;
  DWORD		sendBytes;

  dataBuf.len = size;
  dataBuf.buf = static_cast<char *>pack;

  if (WSASend(this->_sock, &dataBuf, 1, &sendBytes, 0, NULL, NULL) == SOCKET_ERROR)
  {
    std::cerr << "/!\ WSASend error. /!\\" << std::endl;
    closesocket(this->_sock);
  }
}

void		WinUdpSock::

int		WinUdpSock::accept(void)
{
  SOCKET	cltSock;
  int		cltSize = sizeof(this->_cltService);

  if ((cltSock = WSAAccept(this->_sock,
			   static_cast<SOCKADDR *>&this->_cltService,
			   &cltSize,
			   NULL, NULL)) == SOCKET_ERROR)
  {
    std::cerr << "/!\ WSAAccept error. /!\\" << std::endl;
    closesocket(this->_sock);
  }
  return (0); // Il faudrait return un SOCKET.
}

int		WinUdpSock::select()
{
  HWND hwnd;
  WSAAsyncSelect(this->_sock, &hwnd, 0, FD_READ|FD_WRITE);
}

//
// Getteurs
//
const std::string	&getIp() const
{
  return (this->_ip);
}

short		getPort() const
{
  return (this->_port);
}

SOCKET		getSock() const
{
  return (this->_sock);
}

sockaddr_in		&getService() const
{
  return (this->_service);
}

WinUdpSock	&WinUdpSock::operator=(const WinUdpSock &cpy)
{
  this->_ip = cpy.getIp();
  this->_port = cpy.getPort();
  this->_sock = cpy.getSock();
  this->_service = cpy.getService();
  return (*this);
}

WinUdpSock::WinUdpSock(const WinUdpSock &cpy)
{
  *this = cpy;
}

WinUdpSock::WinUdpSock(const std::string &ip, short port)
  : _ip(ip), _port(port)
{
  // faire une verification pour le startup avec le compteur d'instance
  WSADATA	wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
    std::cerr << "/!\ WSAStartup error. /!\\" << std::endl;

  if ((this->_sock = WSASocket(AF_INET,
			       SOCK_STREAM,
			       IPPROTO_UDP,
			       NULL, 0, 0)) == INVALID_SOCKET)
  {
    std::cerr << "/!\ WSASocket error. /!\\" << std::endl;
    WSACleanup();
  }
  this->_service.sin_family = AF_INET;
  this->_service.sin_addr.s_addr = inet_addr(this->_ip.c_str());
  if (WSAHtons(this->_sock, this->_port,
	       &this->service.sin_port) == SOCKET_ERROR)
  {
    std::cerr << "/!\ WSAHtons error. /!\\" << std::endl;
    closesocket(this->_sock);
  }

}

WinUdpSock::WinUdpSock()
{
}

WinUdpSock::~WinUdpSock()
{
  closesocket(this->_sock);
}
