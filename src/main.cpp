#include<iostream>
#include<local_tcp_server.h>

int main(int argc, char** argv) {
  std::cout<<"Hello, World 2!"<<std::endl;
  http::TcpServer server = http::TcpServer("0.0.0.0", 8080);
  server.startListen();
  return 0;
}