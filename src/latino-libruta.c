#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <latino.h>
#include <latino-libnucleoex.h>
#include <latino-libruta.h>

#ifdef _MSC_VER
#include <MSVC/dirent.h>
#else
#include <dirent.h>
#endif

struct DirNodo *crear_dirnodo() {
  struct DirNodo *dirnodo = (struct DirNodo*)malloc(sizeof(struct DirNodo));
  dirnodo->elemento_nombre = NULL;
  dirnodo->sig = NULL;
  return dirnodo;
}

struct DirNodo *_listar_dir(const char* ruta) {
  struct DirNodo *dirnodo = NULL;
  struct DirNodo *siguiente;

  DIR *directorio = opendir(ruta);
  struct dirent *entrada;

  if (directorio) {
    while((entrada = readdir(directorio))){
      if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
        continue;
      }

      if (dirnodo) {
        siguiente->sig = crear_dirnodo();
        siguiente = siguiente->sig;
      } else {
        dirnodo = crear_dirnodo();
        siguiente = dirnodo;
      }

      siguiente->elemento_nombre = (char*)malloc(strlen(entrada->d_name) + 1);
      strcpy(siguiente->elemento_nombre, entrada->d_name);
    }

    dirnodo = (dirnodo) ? dirnodo : crear_dirnodo();
    closedir(directorio);
  }

  return dirnodo;
}

lista *listar_dir(lat_mv *mv, const char *ruta) {
  lista *elementos = latL_crear(mv);
  struct DirNodo *dir = _listar_dir(ruta);

  if (dir) {
    if (dir->elemento_nombre) {
      struct DirNodo *siguiente = dir;

      while (siguiente) {
        lat_objeto *cadena = latC_crear_cadena(mv, siguiente->elemento_nombre);
        latL_agregar(mv, elementos, cadena);

        dir = siguiente;
        siguiente = siguiente->sig;
        free(dir->elemento_nombre);
        free(dir);
      }
    } else {
      free(dir);
    }
  } else {
    latL_destruir(mv, elementos);
    ultimo_error = strerror(errno);
    return NULL;
  }

  return elementos;
}

lista *listar_dir_recursivo(lat_mv *mv, const char *ruta) {
  char *elemento_nombre, *ruta_siguiente;
  lista *ruta_elementos, *elementos, *temp;
  bool separador;
  struct stat elemento_stat;

  lista *lista_elementos = listar_dir(mv, ruta);
  if (!lista_elementos) return NULL;

  elementos = latL_crear(mv);
  separador = ruta[strlen(ruta)-1] == RUTA_SEPARADOR;
  ruta_elementos = latL_crear(mv);

  latL_agregar(mv, ruta_elementos, latC_crear_cadena(mv, ruta));
  latL_agregar(mv, ruta_elementos, latC_crear_lista(mv, lista_elementos));
  latL_agregar(mv, elementos, latC_crear_lista(mv, ruta_elementos));

  LIST_FOREACH(lista_elementos, primero, siguiente, cur) {
    elemento_nombre = getstr(getCadena((lat_objeto*)cur->valor));

    ruta_siguiente = (char*)malloc(
      strlen(ruta) + strlen(elemento_nombre) +
      (separador ? 0:1) + 1
    );

    if (separador) {
      sprintf(
        ruta_siguiente, "%s%s",
        ruta, elemento_nombre);
    } else {
      sprintf(
        ruta_siguiente, "%s%c%s",
        ruta, RUTA_SEPARADOR, elemento_nombre);
    }

    if (stat(ruta_siguiente, &elemento_stat)) {
      free(ruta_siguiente);
      continue;
    }

    if (S_ISDIR(elemento_stat.st_mode)) {
      temp = listar_dir_recursivo(mv, ruta_siguiente);

      if (!temp) {
        latL_limpiar_destruir(mv, elementos);
        free(ruta_siguiente);
        return NULL;
      } else {
        latL_extender(mv, elementos, temp);
        latL_destruir(mv, temp);
      }
    }

    free(ruta_siguiente);
  }

  return elementos;
}

void remover_dir_recursivo(const char *ruta) {
  DIR *directorio;
  struct dirent *entrada;
  char *elemento_ruta;
  struct stat elemento_stat;
  bool separador;

  directorio = opendir(ruta);
  separador = ruta[strlen(ruta)-1] == RUTA_SEPARADOR;

  if (directorio) {
    while((entrada = readdir(directorio))){
      if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
        continue;
      }

      elemento_ruta = (char*)malloc(
        strlen(ruta) + strlen(entrada->d_name) +
        (separador ? 0:1) + 1
      );

      if (separador) {
        sprintf(
          elemento_ruta, "%s%s",
          ruta, entrada->d_name);
      } else {
        sprintf(
          elemento_ruta, "%s%c%s",
          ruta, RUTA_SEPARADOR, entrada->d_name);
      }

      if (stat(elemento_ruta, &elemento_stat)) {
        closedir(directorio);
        free(elemento_ruta);
        return;
      }

      if (S_ISDIR(elemento_stat.st_mode)) {
        remover_dir_recursivo(elemento_ruta);
      } else {
        remove(elemento_ruta);
      }

      free(elemento_ruta);
    }

    closedir(directorio);
    rmdir(ruta);
  }
}

// Librería:

void lat_crear_dir(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *ruta = latC_checar_cadena(mv, obj);

  #ifdef _WIN32
  int result = mkdir(ruta);
  #else
  int result = mkdir(ruta, S_IRWXU);
  #endif

  if (result) {
    generar_error(mv, strerror(errno));
    return;
  }

  latC_apilar(mv, latC_crear_logico(mv, true));
}

void lat_remover_dir(lat_mv *mv) {
  bool recursivo;

  lat_objeto *obj1 = latC_desapilar(mv);
  if (obj1->tipo == T_NULL) {
    recursivo = false;
  } else {
    recursivo = latC_checar_logico(mv, obj1);
  }

  lat_objeto *obj2 = latC_desapilar(mv);
  char *ruta = latC_checar_cadena(mv, obj2);

  DIR *directorio = opendir(ruta);
  struct stat comprobar;

  if (directorio) {
    closedir(directorio);

    if (recursivo) {
      remover_dir_recursivo(ruta);
    } else {
      rmdir(ruta);
    }

    ultimo_error = strerror(errno);

    if (!stat(ruta, &comprobar)) {
      generar_error(mv, ultimo_error);
      return;
    }

    latC_apilar(mv, latC_crear_logico(mv, true));
  } else {
    generar_error(mv, strerror(errno));
  }
}

void lat_listar_dir(lat_mv *mv) {
  bool recursivo;

  lat_objeto *obj1 = latC_desapilar(mv);
  if (obj1->tipo == T_NULL) {
    recursivo = false;
  } else {
    recursivo = latC_checar_logico(mv, obj1);
  }

  lat_objeto *obj2 = latC_desapilar(mv);
  char *ruta = arreglar_ruta(latC_checar_cadena(mv, obj2));

  lista *elementos = (
    recursivo ? listar_dir_recursivo(mv, ruta) : listar_dir(mv, ruta));

  free(ruta);

  if (elementos) {
    latC_apilar(mv, latC_crear_lista(mv, elementos));
  } else {
    generar_error(mv, ultimo_error);
  }
}

void lat_existe(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *ruta = latC_checar_cadena(mv, obj);

  struct stat ruta_stat;
  latC_apilar(mv, latC_crear_logico(mv, !stat(ruta, &ruta_stat)));
}

void lat_es_dir(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *ruta = latC_checar_cadena(mv, obj);

  struct stat ruta_stat;

  if (stat(ruta, &ruta_stat)) {
    generar_error(mv, strerror(errno));
    return;
  }

  latC_apilar(mv, latC_crear_logico(mv, S_ISDIR(ruta_stat.st_mode)));
}

void lat_es_archivo(lat_mv *mv) {
  lat_objeto *obj = latC_desapilar(mv);
  char *ruta = latC_checar_cadena(mv, obj);

  struct stat ruta_stat;

  if (stat(ruta, &ruta_stat)) {
    generar_error(mv, strerror(errno));
    return;
  }

  latC_apilar(mv, latC_crear_logico(mv, S_ISREG(ruta_stat.st_mode)));
}
