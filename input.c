#include "input.h"
#include <stdio.h>

#include <string.h>     /* strerror() */
#include <errno.h>      /* errno */

#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <sys/ioctl.h>  /* ioctl() */

#include <linux/input.h>    /* EVIOCGVERSION ++ */

#define EV_BUF_SIZE 16

void handle_input_event(struct input_event event) {
  fprintf(stderr,
          "%ld.%06ld: "
          "type=%02x "
          "code=%02x "
          "value=%02x\n",
          event.time.tv_sec,
          event.time.tv_usec,
          event.type,
          event.code,
          event.value
          );
}

int loop_read_input_file(char *input_filename) {
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

  fprintf(stderr,
          "Name      : %s\n"
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

    for (i = 0; i < sz / sizeof(struct input_event); ++i) {
      handle_input_event(ev[i]);
    }
  }

 fine:
  close(fd);

  return errno;
}
