################################################################################
# Para mas información de este archivo visite la pagina de cmake:
# https://cmake.org/documentation/
################################################################################

#Establece la versión mínima requerida de cmake para un proyecto.
cmake_minimum_required(VERSION 3.0.2)

#Establece un nombre para el proyecto
project (latino-libnucleoex)

option(MODO_SEGURO_FORZADO "Usar modo seguro forzado" OFF)
option(MODO_SEGURO "Usar modo seguro" OFF)

if(MODO_SEGURO_FORZADO)
  add_definitions(-DMODO_SEGURO_FORZADO)
elseif(MODO_SEGURO)
  add_definitions(-DMODO_SEGURO)
endif()

if(WIN32)
  # Arquitectura del build
  set(TARGET_ARCH_REGEX "^.*-march[= ]([^ ]+).*$")
  string(REGEX MATCH "${TARGET_ARCH_REGEX}" TARGET_ARCH_MATCH "" "" ${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS})
  if(TARGET_ARCH_MATCH)
      string(REGEX REPLACE "${TARGET_ARCH_REGEX}" "\\1" TARGET_ARCH ${CMAKE_C_FLAGS} ${CMAKE_CXX_FLAGS})
  else()
      set(TARGET_ARCH  ${CMAKE_HOST_SYSTEM_PROCESSOR})
  endif()

  # Establecer paths donde se instalo latino
  set(LATINO_PATH "$ENV{LATINO_PATH}/bin" CACHE FILEPATH "Ruta de instalacion de latino.exe")
  set(LATINO_LIBC "$ENV{LATINO_LIBC}" CACHE FILEPATH "Ruta de instalacion de latino.dll")
  set(LATINO_INCLUDE "$ENV{LATINO_PATH}/include" CACHE FILEPATH "Ruta de instalacion de latino/include")

  # Enlazar
  include_directories(${LATINO_INCLUDE} "include")
  link_directories(${LATINO_PATH})

  message(STATUS "TARGET_ARCH: ${TARGET_ARCH}")
  message(STATUS "LATINO_PATH: ${LATINO_PATH}")
  message(STATUS "LATINO_INCLUDE: ${LATINO_INCLUDE}")
  message(STATUS "LATINO_LIBC: ${LATINO_LIBC}")
else()
  include_directories("include")
endif()

# msys
if(MSYS)
  # Path en donde esta instalado latino
  LINK_DIRECTORIES("/d/work/lenguaje-latino/latino/msys2")
endif()

set(SRC_FILES src/latino-libnucleoex.c src/latino-libtipos.c src/latino-libruta.c src/latino-libes.c)

#Agrega una biblioteca al proyecto utilizando los
if(MINGW)
  #archivos de origen especificados.
  set(CMAKE_SHARED_LIBRARY_PREFIX "")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--allow-multiple-definition")
  add_library(latino-libnucleoex SHARED ${SRC_FILES})
  target_link_libraries(latino-libnucleoex ${LATINO_PATH}/latino.dll)
else()
  #archivos de origen especificados.
  add_library(latino-libnucleoex SHARED ${SRC_FILES})

  #Vincula un objetivo a bibliotecas determinadas.
  target_link_libraries(latino-libnucleoex latino)
endif()

#Especifica las reglas que se ejecutarán en el momento de la instalación.
# Especifica las reglas que se ejecutarán en el momento de la instalación.
if(WIN32)
  install(TARGETS latino-libnucleoex DESTINATION ${LATINO_PATH})
else()
  install(TARGETS latino-libnucleoex DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endif()