#include <unistd.h>
#include "input.h"
#include "control.h"


int main(int argc, char *argv[]) {
    char path[25];
  
    init_robot();
    move_fwd();
    sleep(2);
    stop_moving();
    
    //find_remote_control_device(path);
    //loop_read_input_file(path);
    return 0;
}

