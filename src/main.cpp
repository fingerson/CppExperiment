#include <iostream>
#include <crow.h>
#include <xdo_interface.h>


int main(int argc, char** argv) {
  std::cout<<"Hello, World 2!"<<std::endl;
  crow::SimpleApp app;
  crow::mustache::set_global_base("src/templates");

  CROW_ROUTE(app, "/")([](){
    std::string page = crow::mustache::load_text("fancypage.html");
    return page;
  });

  CROW_ROUTE(app,"/click/<int>/<int>")([](int x, int y){
    std::cout<<"Started action\n";
    xdo_interface::mouse_move(x,y);
    std::cout<<"Moved mouse\n";
    xdo_interface::mouse_click();
    std::cout<<"Clicked\n";
    std::string page = crow::mustache::load_text("clicked.html");
    return page;
  });

  app.port(18080).multithreaded().run();


  return 0;
}