/* Copyright StrongLoop, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// crash handle
#include <signal.h>
#include <unistd.h>
#include <dep/crashhandler/crashhandler.h>
#define FILE_PATH_LEN 1024

#if HAVE_UNISTD_H
#include <unistd.h>  /* getopt */
#endif

//#define DEFAULT_BIND_HOST     "127.0.0.1"
#define DEFAULT_BIND_HOST     "0.0.0.0"
//#define DEFAULT_BIND_PORT     1080
#define DEFAULT_BIND_PORT     8081
#define DEFAULT_IDLE_TIMEOUT  (60 * 1000)

static void parse_opts(server_config *cf, int argc, char **argv);
static void usage(void);

static const char *progname = __FILE__;  /* Reset in main(). */

// TODO
void crash_proc(int sig)
{
  if (fork() != 0)
  {
      signal(sig, SIG_DFL);
      kill(getpid(), sig);
      return;
  }

  //child process
  char* p_base = ".";
  char  path_base[FILE_PATH_LEN];
  char  filename[FILE_PATH_LEN];

  sprintf(path_base, p_base);
  p_base = path_base;

  sprintf(filename, "%s/log", p_base);

  handle_crash(filename, progname);
}

int main(int argc, char **argv) {
  server_config config;
  int err;

  signal(SIGSEGV, crash_proc);

  progname = argv[0];
  memset(&config, 0, sizeof(config));
  config.bind_host = DEFAULT_BIND_HOST;
  config.bind_port = DEFAULT_BIND_PORT;
  config.idle_timeout = DEFAULT_IDLE_TIMEOUT;
  parse_opts(&config, argc, argv);

  err = server_run(&config, uv_default_loop());
  if (err) {
    abort();
    //exit(1);
  }
  abort();

  return 0;
}

const char *_getprogname(void) {
  return progname;
}

static void parse_opts(server_config *cf, int argc, char **argv) {
  int opt;

  while (-1 != (opt = getopt(argc, argv, "H:hp:"))) {
    switch (opt) {
      case 'H':
        cf->bind_host = optarg;
        break;

      case 'p':
        if (1 != sscanf(optarg, "%hu", &cf->bind_port)) {
          pr_err("bad port number: %s", optarg);
          usage();
        }
        break;

      default:
        usage();
    }
  }
}

static void usage(void) {
  printf("Usage:\n"
         "\n"
         "  %s [-b <address> [-h] [-p <port>]\n"
         "\n"
         "Options:\n"
         "\n"
         "  -b <hostname|address>  Bind to this address or hostname.\n"
         "                         Default: \"127.0.0.1\"\n"
         "  -h                     Show this help message.\n"
         "  -p <port>              Bind to this port number.  Default: 1080\n"
         "",
         progname);
  abort();
  //exit(1);
}
