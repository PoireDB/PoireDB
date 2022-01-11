#include "../include/util/string.h"

char *format(const char *format, ...)
{
  va_list arguments;
  va_start(arguments, format);
  char *string = formatv(format, arguments);
  va_end(arguments);
  return string;
}

char *formatv(const char *format, va_list arguments)
{
  va_list again;
  va_copy(again, arguments);
  int length = vsnprintf(NULL, 0, format, arguments) + 1;
  char *out = calloc(length, sizeof(char));
  vsnprintf(out, length, format, again);
  return out;
}