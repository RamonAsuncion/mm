#include "../include/sysdeps.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

void *xmalloc(size_t size) { return malloc(size); }
void *xcalloc(size_t nmemb, size_t size) { return calloc(nmemb, size); }
void xfree(void *ptr) { free(ptr); }

int xprintf(const char *fmt, ...) {
  va_list ap; va_start(ap, fmt);
  int r = vprintf(fmt, ap);
  va_end(ap);
  return r;
}
