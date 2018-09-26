// Find the /dev/input/eventN path that corresponds to
// the 123 COM Smart Control USB device.
extern int find_remote_control_device();

extern void listen_to_arrow_keys();

// Once the device is found, we open it, and read commands
// from the file, such as which direction the robot should move.
//
// This function writes the input file path to the argument string
extern int loop_read_input_file(char []);
