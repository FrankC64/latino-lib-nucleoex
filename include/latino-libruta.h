#ifndef LATINO_LIBRUTA
#define LATINO_LIBRUTA

#include <latino.h>

#ifdef _WIN32
#define RUTA_SEPARADOR '\\'
#else
#define RUTA_SEPARADOR '/'
#endif

#define LIBRUTA "libruta"

struct DirNodo {
  char *elemento_nombre;
  struct DirNodo *sig;
};

struct DirNodo *crear_dirnodo();

void lat_crear_dir(lat_mv *mv);
void lat_remover_dir(lat_mv *mv);
void lat_listar_dir(lat_mv *mv);
void lat_es_dir(lat_mv *mv);
void lat_es_archivo(lat_mv *mv);
void lat_existe(lat_mv *mv);

static const lat_CReg lib_ruta[] = {
	{"crear_dir", lat_crear_dir, 1},
  {"crear_directorio", lat_crear_dir, 1},
  {"remover_dir", lat_remover_dir, 2},
  {"remover_directorio", lat_remover_dir, 2},
  {"listar_dir", lat_listar_dir, 2},
  {"listar_directorio", lat_listar_dir, 2},
  {"existe", lat_existe, 1},
	{"es_dir", lat_es_dir, 1},
	{"es_directorio", lat_es_dir, 1},
	{"es_archivo", lat_es_archivo, 1},
  {NULL, NULL, 0}
};

#endif
