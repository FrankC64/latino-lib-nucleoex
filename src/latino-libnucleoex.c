#ifdef _WIN32
#define LATINO_BUILD_AS_DLL
#endif

#define LATINO_LIB

#include <stdlib.h>
#include <string.h>
#include <latino.h>
#include <latino-libnucleoex.h>

#if (defined MODO_SEGURO_FORZADO) || (defined MODO_SEGURO)
bool modo_seguro = true;
#else
bool modo_seguro = false;
#endif

char *ultimo_error = NULL;

void generar_error(lat_mv *mv, char *error) {
  if (modo_seguro) {
    ultimo_error = error;
  } else {
    latC_error(mv, error);
  }
}

char *arreglar_ruta(const char *ruta) {
  char *nueva_ruta = malloc(strlen(ruta) + 1);
  strcpy(nueva_ruta, ruta);

  char reemplazar = RUTA_SEPARADOR == '/' ? '\\' : '/';

  for (int i=0;nueva_ruta[i];i++) {
    if (nueva_ruta[i] == reemplazar) {
      nueva_ruta[i] = RUTA_SEPARADOR;
    }
  }

  return nueva_ruta;
}

void lat_establecer_modo_seguro(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  bool modo = latC_checar_logico(mv, obj);

  #ifndef MODO_SEGURO_FORZADO
  modo_seguro = modo;
  #endif
}

void lat_modo_seguro_estado(lat_mv *mv) {
  latC_apilar(mv, latC_crear_logico(mv, modo_seguro));
}

void lat_modo_seguro_forzado(lat_mv *mv) {
  #ifdef MODO_SEGURO_FORZADO
  latC_apilar(mv, latC_crear_logico(mv, true));
  #else
  latC_apilar(mv, latC_crear_logico(mv, false));
  #endif
}

void lat_ultimo_error(lat_mv *mv) {
  if (ultimo_error) {
    latC_apilar_string(mv, ultimo_error);
    ultimo_error = NULL;
  } else {
    latC_apilar_string(mv, "");
  }
}

void lat_generar_error(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *error = latC_checar_cadena(mv, obj);
  latC_error(mv, error);
}

void lat_version(lat_mv *mv) {
  latC_apilar(mv, latC_crear_cadena(mv, LIBNUCLEOEX_VERSION));
}

LATINO_API void latC_abrir_liblatino_libnucleoex(lat_mv *mv) {
  latC_abrir_liblatino(mv, LIBNUCLEOEX, lib_nucleoex);
  latC_abrir_liblatino(mv, LIBRUTA, lib_ruta);
  latC_abrir_liblatino(mv, LIBES, lib_es);
}
