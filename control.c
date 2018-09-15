#include "gopigo.h"

void init_robot() {
    // Buffer for data being read/ written on the i2c bus
    if(init()==-1) {
        exit(1);
    }
    led_on(1);
}

void move_fwd() {
    fwd();
}

void move_left() {
    left();
}

void move_right() {
    right();
}

void move_back() {
    bwd();
}

void slow_down() {
    decrease_speed();
}

void speed_up() {
    increase_speed();
}

void stop_moving() {
    stop();
} 

