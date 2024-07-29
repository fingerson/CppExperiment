#ifndef XDOTOOL_LOCAL_INTERFACE
#define XDOTOOL_LOCAL_INTERFACE

#include <utility>
extern "C" {
  #include "xdo.h"
}

namespace xdo_interface {

  class XdoInterface {
    public:
      XdoInterface();
      ~XdoInterface();
      void mouse_move(int x, int y);
      std::pair<int,int> mouse_position();
      std::pair<int,int> screen_size();  
      void mouse_click();
    private:
      xdo_t *xdo_obj;
  };
  
}


#endif