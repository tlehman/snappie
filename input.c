#include "input.h"
#include "control.h"
#include <stdio.h>

#include <string.h>     /* strerror() */
#include <errno.h>      /* errno */

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <sys/ioctl.h>  /* ioctl() */

#include <signal.h>

int fd;
void sig_handler(int signo) {
  if(signo == SIGTERM) {
    stop_moving(); // stop those wheels, snappie
    close(fd); // close device file
  }
}

#include <linux/input.h>    /* EVIOCGVERSION ++ */

#define EV_BUF_SIZE 16

void handle_input_event(struct input_event event) {
    if(event.value == 458833) {
		move_forward();
    } else if(event.value == 458834) {
		move_back();
    } else {
		stop();
    }
}

int is_correct_input_type(char *input_filename) {
    unsigned short id[4];                   /* or use struct input_id */
    char name[256] = "N/A";

    if ((fd = open(input_filename, O_RDONLY)) < 0) {
      fprintf(stderr,
              "ERR %d:\n"
              "Unable to open `%s'\n"
              "%s\n",
              errno, input_filename, strerror(errno)
              );
    }
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);

	printf("DEBUG: %s in %s\n", name, input_filename);

    close(fd);
    return strcmp(name, "Knorvay USB Device") == 0;
}

int loop_read_input_file(char input_filename[]) {
    int fd, sz;
    unsigned i;

    /* A few examples of information to gather */
    unsigned version;
    unsigned short id[4];                   /* or use struct input_id */
    char name[256] = "N/A";

    struct input_event ev[EV_BUF_SIZE]; /* Read up to N events ata time */

    if ((fd = open(input_filename, O_RDONLY)) < 0) {
      fprintf(stderr,
              "ERR %d:\n"
              "Unable to open `%s'\n"
              "%s\n",
              errno, input_filename, strerror(errno)
              );
    }
    /* Error check here as well. */
    ioctl(fd, EVIOCGVERSION, &version);
    ioctl(fd, EVIOCGID, id);
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);

    printf("Name      : %s\n"
           "Version   : %d.%d.%d\n"
           "ID        : Bus=%04x Vendor=%04x Product=%04x Version=%04x\n"
           "----------\n"
           ,
           name,

           version >> 16,
           (version >> 8) & 0xff,
           version & 0xff,

           id[ID_BUS],
           id[ID_VENDOR],
           id[ID_PRODUCT],
           id[ID_VERSION]
           );

    /* Loop. Read event file and parse result. */
    init_robot();
    for (;;) {
      sz = read(fd, ev, sizeof(struct input_event) * EV_BUF_SIZE);

      if (sz < (int) sizeof(struct input_event)) {
        fprintf(stderr,
                "ERR %d:\n"
                "Reading of `%s' failed\n"
                "%s\n",
                errno, input_filename, strerror(errno)
                );
        goto fine;
      }

	  for (i = 0; i < sz / sizeof(struct input_event); i+=10) {
		handle_input_event(ev[i]);
	  }
    }

 fine:
    close(fd);

    return errno;
}

#include <sys/types.h>
#include <dirent.h>

int find_remote_control_device() {
    struct dirent *de;
    DIR *dr = opendir("/dev/input");
    if (dr == NULL) {
        printf("Could not open current directory" );
        return 1;
    }
    char path[25];
    while ((de = readdir(dr)) != NULL) {
      sprintf(path, "/dev/input/%s", de->d_name);
      if(is_correct_input_type(path)) {
        printf("found %s as remote control device\n", path);
        loop_read_input_file(path);
      }
    }
    return closedir(dr);
}


void listen_to_arrow_keys() {
    int c;
	while((c = getc(stdin)) != '#') {
		switch(c) {
			case KEY_UP:
				printf("up\n");
			case KEY_DOWN:
				printf("down\n");
			default: 
				printf("c = %d\n");
        }
    }
}

