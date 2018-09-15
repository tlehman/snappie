#include "input.h"

int main(int argc, char *argv[]) {
  char* path = "/dev/input/event19";
  loop_read_input_file(path);
  return 0;
}

