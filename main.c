#include "input.h"

int main(int argc, char *argv[]) {
  char path[25];
  find_remote_control_device(path);
  //loop_read_input_file("/dev/input/event19");
  return 0;
}

