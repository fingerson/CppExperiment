#include<iostream>
#include<crow.h>

int main(int argc, char** argv) {
  std::cout<<"Hello, World 2!"<<std::endl;
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")([](){
    return "Hello World!";
  });

  app.port(18080).multithreaded().run();

  return 0;
}