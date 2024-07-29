#include <local_tcp_server.h>

#include <iostream>
#include <sstream>
#include <unistd.h>
#include <utils.h>


namespace {

  const int BUFFER_SIZE = 30720;

  
}

namespace http {

  class TcpServerImp {
    public:
      TcpServerImp(std::string ip_address, int port);
      ~TcpServerImp();
      void startListen();
      int m_socket;
      int m_new_socket;
      int m_port;
      long m_incomingMessage;
      struct sockaddr_in m_socketAddress;
      unsigned int m_socketAddress_len;
      std::string m_serverMessage;
      std::string m_ip_address;

      int startServer();
      void closeServer();
      std::string buildResponse();
      void acceptConnection(int &new_socket);
      void sendResponse();
  };

  TcpServerImp::TcpServerImp(std::string ip_address, int port) :
    m_ip_address(ip_address), m_port(port), m_socket(), m_incomingMessage(),
    m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
    m_serverMessage(buildResponse()), m_new_socket()
  {
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_port = htons(m_port);
    m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
    
    if (startServer() != 0) {
      std::ostringstream ss;
      ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
      utils::log(ss.str());
    }
  }

  TcpServerImp::~TcpServerImp() {
    closeServer();
  }

  int TcpServerImp::startServer() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket < 0) {
      utils::exitWithError("Cannot create socket");
      return 1;
    }
    if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
      utils::exitWithError("Cannot connect socket to address");
      return 1;
    }
    return 0;
  }

  void TcpServerImp::closeServer() {
    close(m_socket);
    close(m_new_socket);
    exit(0);
  }

  void TcpServerImp::startListen()
  {
      if (listen(m_socket, 20) < 0)
      {
          utils::exitWithError("Socket listen failed");
      }

      std::ostringstream ss;
      ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
      utils::log(ss.str());

      int bytesReceived;

      while (true)
      {
          utils::log("====== Waiting for a new connection ======\n\n\n");
          acceptConnection(m_new_socket);

          char buffer[BUFFER_SIZE] = {0};
          bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
          if (bytesReceived < 0)
          {
              utils::exitWithError("Failed to read bytes from client socket connection");
          }
          std::ostringstream bs;
          bs << buffer;
          utils::log("Received data: " + bs.str());

          std::ostringstream ss;
          ss << "------ Received Request from client ------\n\n";
          utils::log(ss.str());

          sendResponse();

          close(m_new_socket);
      }
  }

  void TcpServerImp::acceptConnection(int &new_socket)
  {
      new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
      if (new_socket < 0)
      {
          std::ostringstream ss;
          ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
          utils::exitWithError(ss.str());
      }
  }

  std::string TcpServerImp::buildResponse()
  {
      std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
      std::ostringstream ss;
      ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
          << htmlFile;

      return ss.str();
  }

  void TcpServerImp::sendResponse()
  {
      long bytesSent;

      bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());

      if (bytesSent == m_serverMessage.size())
      {
          utils::log("------ Server Response sent to client ------\n\n");
      }
      else
      {
          utils::log("Error sending response to client");
      }
  }

  TcpServer::TcpServer(std::string ip_address, int port) : pimpl_( new TcpServerImp(ip_address, port) ) {
  }

  TcpServer::~TcpServer() {
    delete pimpl_;
  }

  void TcpServer::startListen() {
    pimpl_ -> startListen();
  }

}