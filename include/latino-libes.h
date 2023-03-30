#ifndef LATINO_LIBES
#define LATINO_LIBES

#include <latino.h>

#define LIBES "libes"

void lat_imprimir(lat_mv *mv);

static const lat_CReg lib_es[] = {
  {"imprimir", lat_imprimir, 1},
  {"escribir", lat_imprimir, 1},
  {"poner", lat_imprimir, 1},
  {NULL, NULL, 0}
};

#endif
