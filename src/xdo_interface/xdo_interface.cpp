#include <xdo_interface.h>
#include <unistd.h>
#include <string>

namespace xdo_interface {

  XdoInterface::XdoInterface(): xdo_obj(xdo_new(nullptr)) {
  }

  XdoInterface::~XdoInterface() {
    xdo_free(xdo_obj);
  }

  void XdoInterface::mouse_move(int x, int y) {

    char *args[] = {"xdotool","mousemove",&std::to_string(x)[0],&std::to_string(y)[0],nullptr};
    fork();
    if (fork() == 0) {
      execvp("xdotool", args);
    }
  }
  std::pair<int,int> XdoInterface::mouse_position() {
    return std::pair<int,int>(0,0);
  }
  std::pair<int,int> XdoInterface::screen_size() {
    return std::pair<int,int>(0,0);
  }
  void XdoInterface::mouse_click() {
    char *args[] = {"xdotool","click","1",nullptr};
    if (fork() == 0) {
      execvp("xdotool", args);
    }
  }
}