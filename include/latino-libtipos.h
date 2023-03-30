#ifndef LATINO_LIBTIPOS
#define LATINO_LIBTIPOS

#include <wchar.h>
#include <latino.h>

#define LIBTIPOS "libtipos"

int utf8_longitud(const char *cadena);
wchar_t *utf8_a_utf16(const char *cadena_utf8);

#endif
