/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
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

#include "uv.h"
#include "internal.h"

#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/sysctl.h>


#if defined(__linux__)
  /* TODO: */
#elif defined(__sun)
  /* TODO: */
#elif defined(__DragonFly__)  || \
      defined(__FreeBSD__)    || \
      defined(__OpenBSD__)    || \
      defined(__NetBSD__)     || \
      defined(__APPLE__)
static char *process_title;
#endif


uv_err_t uv__platform_set_process_title(const char* title) {

#if defined(__linux__)
  /* TODO: */
#elif defined(__sun)
  /* TODO: */
#elif defined(__DragonFly__)  || \
      defined(__FreeBSD__)    || \
      defined(__OpenBSD__)    || \
      defined(__NetBSD__)     || \
      defined(__APPLE__)
  int oid[4];

  if (process_title) {
    free(process_title);
  }
  process_title = strdup(title);

  oid[0] = CTL_KERN;
  oid[1] = KERN_PROC;
#if defined(__APPLE__)
  oid[2] = KERN_PROCARGS;
#elif
  oid[2] = KERN_PROC_ARGS;
#endif
  oid[3] = getpid();

  sysctl(oid,
         ARRAY_SIZE(oid),
         NULL,
         NULL,
         process_title,
         strlen(process_title) + 1);
#endif

  return uv_ok_;
}


uv_err_t uv__platform_get_process_title(char* buffer, size_t size) {

#if defined(__linux__)
  /* TODO: */
#elif defined(__sun)
  /* TODO: */
#elif defined(__DragonFly__)  || \
      defined(__FreeBSD__)    || \
      defined(__OpenBSD__)    || \
      defined(__NetBSD__)     || \
      defined(__APPLE__)
  if (process_title) {
    strncpy(buffer, process_title, size);
  } else {
    if (size > 0) {
      buffer[0] = '\0';
    }
  }
#endif

  return uv_ok_;
}

