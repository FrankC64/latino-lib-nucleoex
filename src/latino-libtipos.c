#include <stdlib.h>
#include <stdint.h>
#include <wchar.h>
#include <latino.h>
#include <latino-libnucleoex.h>
#include <latino-libtipos.h>

int utf8_longitud(const char *cadena) {
  int len = 0;
  while (*cadena != '\0') {
    if ((*cadena & 0xc0) != 0x80) {
      len++;
    }
    cadena++;
  }
  return len;
}

wchar_t *utf8_a_utf16(const char *cadena_utf8) {
  int len = utf8_longitud(cadena_utf8);

  wchar_t *cadena_utf16 = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));

  int i = 0;
  while (*cadena_utf8 != '\0') {
    uint32_t codepoint;
    int bytes;

    if ((*cadena_utf8 & 0x80) == 0) {
      codepoint = *cadena_utf8 & 0x7f;
      bytes = 1;
    } else if ((*cadena_utf8 & 0xe0) == 0xc0) {
      codepoint = *cadena_utf8 & 0x1f;
      bytes = 2;
    } else if ((*cadena_utf8 & 0xf0) == 0xe0) {
      codepoint = *cadena_utf8 & 0x0f;
      bytes = 3;
    } else if ((*cadena_utf8 & 0xf8) == 0xf0) {
      codepoint = *cadena_utf8 & 0x07;
      bytes = 4;
    } else {
      free(cadena_utf16);
      return NULL;
    }

    for (int j = 1; j < bytes; j++) {
      if ((cadena_utf8[j] & 0xc0) != 0x80) {
        free(cadena_utf16);
        return NULL;
      }
      codepoint = (codepoint << 6) | (cadena_utf8[j] & 0x3f);
    }
    cadena_utf8 += bytes;

    if (codepoint < 0x10000) {
      cadena_utf16[i++] = (wchar_t)codepoint;
    } else {
      codepoint -= 0x10000;
      cadena_utf16[i++] = (wchar_t)((codepoint >> 10) | 0xd800);
      cadena_utf16[i++] = (wchar_t)((codepoint & 0x3ff) | 0xdc00);
    }
  }

  cadena_utf16[i] = L'\0';
  return cadena_utf16;
}
