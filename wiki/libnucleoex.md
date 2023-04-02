Funciones de configuración de la librería.

### <code>libnucleoex.establecer_modo_seguro(*modo*)</code>
> Establece el estado del modo seguro. Si la librería se encuentra compilada en modo seguro forzado esta función no surtirá efecto. <br><br>
> Argumentos:<br>
> ***modo***: Acepta un lógico (verdadero/falso) que determinará el estado del modo seguro, donde **verdadero** habilita el modo seguro y **falso** lo inhabilita.

<br>

### <code>libnucleoex.modo_seguro_estado()</code>
> Retorna un lógico (verdadero/falso) que indica el estado actual del modo seguro. Si la librería está compilada en modo seguro forzado esta función siempre retornará **verdadero**.

<br>

> Retorna una cadena correspondiente al último mensaje de error ocurrido. Los mensajes de error solo se registran con el modo seguro activo.

<br>

### <code>libnucleoex.generar_error(*mensaje*)</code>
> Provoca o lanza un error en **Latino** con un mensaje personalizado. Esta función no está sujeta al modo seguro, por lo que independientemente del estado el error será lanzado. <br><br>
> Argumentos:<br>
> ***mensaje***: Acepta una cadena que será impresa como el mensaje del error.

<br>

### <code>libnucleoex.version()</code>
> Retorna una cadena de texto que indica la versión actual de la librería.
