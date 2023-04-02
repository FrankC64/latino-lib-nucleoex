!Bienvenido a la Wiki de **latino-liblatino**¡
Aquí podrá encontrar todo lo que necesita para conocer las funciones integradas en la librería.

|[libnucleoex](https://github.com/FrankC64/latino-lib-nucleoex/wiki/libnucleoex)|
|:------------------------------------------------------------------------------|
|Funciones de configuración de la librería.                                     |

|[libruta](https://github.com/FrankC64/latino-lib-nucleoex/wiki/libruta)|
|:----------------------------------------------------------------------|
|Funciones para la manipulación de rutas, archivos y carpetas.          |

|[libes](https://github.com/FrankC64/latino-lib-nucleoex/wiki/libes)|
|:------------------------------------------------------------------|
|Funciones para entrada y salida (impresión, archivos, etc.).       |

## Modo seguro
\- **¿Qué es el modo seguro?** <br>
El modo seguro es una propiedad de la librería, implementada con el fin de prevenir que se detenga el curso del código por algún error generado por la librería. Esta propiedad está integrada a causa de que al momento de sacar esta versión, **Latino** no tiene forma de capturar errores y excepciones.

\- **¿Cómo funciona el modo seguro?** <br>
El modo seguro lo que hace es capturar el error provocado y almacenarlo para su posterior obtención.

\- **¿Cómo sé si ocurrió un error teniendo el modo seguro activo?** <br>
Puede darse cuenta de esto comprobando el valor devuelto por las funciones. Si la función llamada devuelve **nulo**, en vez de **verdadero** o el valor esperado, puede estar seguro de que se ha producido un error y podrá recuperar el mensaje de error llamando a la función: **libnucleoex.ultimo_error()**.

Nota: La función **libnucleoex.establecer_modo_seguro()** siempre retorna **nulo**, esto así para evitar que la función se intente usar como un sustituto de **libnucleoex.modo_seguro_estado()**.

\- **¿Por qué el modo seguro no se inhabilita?** <br>
Si esto le sucede significa que la librería ha sido compilada con la opción de "modo seguro forzado" y no podrá hacer nada para deshacer esto, a no ser que recompile la librería. Si quiere asegurarse de que su compilación tiene activa esta propiedad, puede comprobarlo llamando a la función **libnucleoex.modo_seguro_forzado()** donde le será retornado un lógico (verdadero/falso) que indicará el estado del "modo seguro forzado".
