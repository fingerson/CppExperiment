#include <xdo_interface.h>
#include <unistd.h>
#include <string>
#include <iostream>

namespace xdo_interface {

  XdoInterface::XdoInterface(): xdo_obj(xdo_new(NULL)) {
  }

  XdoInterface::~XdoInterface() {
    xdo_free(xdo_obj);
  }

  void XdoInterface::mouse_move(int x, int y) {
    xdo_move_mouse_relative(xdo_obj, x, y);
  }
  std::pair<int,int> XdoInterface::mouse_position() {
    return std::pair<int,int>(0,0);
  }
  std::pair<int,int> XdoInterface::screen_size() {
    return std::pair<int,int>(0,0);
  }
  void XdoInterface::mouse_click() {
    Window window;
    xdo_get_window_at_mouse(xdo_obj, &window);
    xdo_mouse_down(xdo_obj, window,1);
    xdo_mouse_up(xdo_obj, window,1);
  }
}