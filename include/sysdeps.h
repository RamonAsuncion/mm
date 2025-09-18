// Implementations forward to libc for now - later can be replaced with my OS functions
#ifndef _SYSDEPS_H_
#define _SYSDEPS_H_

#include <stddef.h>

void *xmalloc(size_t size);
void *xcalloc(size_t nmemb, size_t size);
void xfree(void *ptr);
int xprintf(const char *fmt, ...);

#endif /* _SYSDEPS_H_ */
