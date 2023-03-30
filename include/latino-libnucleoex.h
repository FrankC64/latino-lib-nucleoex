#ifndef LATINO_LIBNUCLEOEX
#define LATINO_LIBNUCLEOEX

#define LIBNUCLEOEX_VERSION "0.0.1"

#include <latino.h>
#include <latino-libruta.h>
#include <latino-libes.h>
#include <latino-libtipos.h>

#define LIBNUCLEOEX "libnucleoex"

extern bool modo_seguro;
extern char *ultimo_error;

void generar_error(lat_mv *mv, char *error);
bool hay_mas_argumentos(lat_mv *mv);
char *arreglar_ruta(const char *ruta);

void lat_establecer_modo_seguro(lat_mv *mv);
void lat_modo_seguro_estado(lat_mv *mv);
void lat_modo_seguro_forzado(lat_mv *mv);
void lat_ultimo_error(lat_mv *mv);
void lat_generar_error(lat_mv *mv);
void lat_version(lat_mv *mv);

static const lat_CReg lib_nucleoex[] = {
  {"establecer_modo_seguro", lat_establecer_modo_seguro, 1},
  {"modo_seguro_estado", lat_modo_seguro_estado, 0},
  {"modo_seguro_forzado", lat_modo_seguro_forzado, 0},
  {"ultimo_error", lat_ultimo_error, 0},
  {"generar_error", lat_generar_error, 1},
	{"version", lat_version, 0},
  {NULL, NULL, 0}
};

#endif
