#include <wchar.h>
#include <locale.h>
#include <fcntl.h>
#include <latino.h>
#include <latino-libnucleoex.h>
#include <latino-libes.h>
#include <latino-libtipos.h>

void lat_imprimir(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *cadena = latC_checar_cadena(mv, obj);

  wchar_t *cadena_utf16 = utf8_a_utf16(cadena);

  if (!cadena_utf16) {
      generar_error(mv, "La cadena de texto no puede ser impresa.");
  } else {

#ifdef _WIN32
  int modo_prev = _setmode(_fileno(stdout), _O_U8TEXT);
  wprintf(L"%ls", cadena_utf16);
  _setmode(_fileno(stdout), modo_prev);
#else
  const char *locale_prev = setlocale(LC_CTYPE, NULL);
  setlocale(LC_CTYPE, "en_US.UTF-8");
  wprintf(L"%ls", cadena_utf16);
  setlocale(LC_CTYPE, locale_prev);
#endif

  free(cadena_utf16);   
  latC_apilar(mv, latC_crear_logico(mv, true));
  }
}
