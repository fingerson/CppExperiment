#include<iostream>
#include<crow.h>

int main(int argc, char** argv) {
  std::cout<<"Hello, World 2!"<<std::endl;
  crow::SimpleApp app;
  crow::mustache::set_global_base("src/templates");

  CROW_ROUTE(app, "/")([](){
    std::string page = crow::mustache::load_text("fancypage.html");
    return page;
  });

  app.port(18080).multithreaded().run();

  return 0;
}