#include "input.h"

int main(int argc, char *argv[]) {
  loop_read_input_file("/dev/input/event20");
  return 0;
}

