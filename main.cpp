#include "input.h"

int main(int argc, char *argv[]) {
  char input_filename[] = "/dev/input/event21";
  loop_read_input_file(input_filename);
  return 0;
}

