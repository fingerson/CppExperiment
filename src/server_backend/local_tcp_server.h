#ifndef LOCAL_TCP_SERVER
#define LOCAL_TCP_SERVER

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string>

namespace http {
  
  class TcpServerImp;

  class TcpServer {
    public:
      TcpServer(std::string ip_address, int port);
      ~TcpServer();
      void startListen();
    
    private:
      TcpServerImp *pimpl_;
  };

}

#endif