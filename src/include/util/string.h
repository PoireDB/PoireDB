#ifndef _UTIL_STRING_H_
#define _UTIL_STRING_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

char *format(const char *format, ...);
char *formatv(const char *format, va_list arguments);

#endif /* _UTIL_STRING_H_ */