Funciones para la manipulación de rutas, archivos y carpetas.

### <code>libruta.crear_dir(*ruta*)</code> o <code>libruta.crear_directorio(*ruta*)</code>
> Crea un directorio en la ruta dada. <br>
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto con la ruta dónde será creado el directorio.

<br>

### <code>libruta.remover_dir(*ruta*, *recursivo*)</code> o <code>libruta.remover_directorio(*ruta*, *recursivo*)</code>
> Elimina el directorio dado como argumento. En la siguiente tabla se muestra cómo trabaja la función: <br>
>
> |Función|Situación|Resultado|
> |-------|---------|---------|
> |libruta.remover_dir("carpeta") <br> libruta.remover_dir("carpeta", falso) <br> libruta.remover_dir("carpeta", nulo)|El directorio está vacía.|Se elimina la carpeta.|
> |libruta.remover_dir("carpeta") <br> libruta.remover_dir("carpeta", falso) <br> libruta.remover_dir("carpeta", nulo)|El directorio no está vacío.|La función falla.|
> |libruta.remover_dir("carpeta", verdadero)|El directorio está vacío.|Se elimina el directorio.|
> |libruta.remover_dir("carpeta", verdadero)|El directorio no está vacío.|Se elimina el directorio.|
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto que contiene la ruta del directorio. <br>
> ***recursivo*** (opcional): Un lógico (verdadero/falso) o nulo que determinará si el directorio será eliminada de forma recursiva.

<br>

### <code>libruta.listar_dir(*ruta*, *recursivo*)</code> o <code>libruta.listar_directorio(*ruta*, *recursivo*)</code>
> Lista las carpetas y archivos de un directorio. Ejemplo de cómo trabaja la función: <br>
> - libruta.listar_dir("ruta"): retorna una lista con las carpetas y archivos contenidos en el directorio. <br>
> - libruta.listar_dir("ruta", verdadero): retorna una lista de listas con las carpetas y archivos contenidos en el directorio y sus sub-carpetas.
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto que contiene la ruta del directorio. <br>
> ***recursivo*** (opcional): Un lógico (verdadero/falso) o nulo que determinará si el directorio será analizado de forma recursiva.

<br>

### <code>libruta.existe(*ruta*)</code>
> Retorna un lógico (verdadero/falso) que determina si el directorio o archivo existe. <br>
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto que contiene la ruta del directorio. <br>

<br>

### <code>libruta.es_dir(*ruta*)</code> o <code>libruta.es_directorio(*ruta*)</code>
> Retorna un lógico (verdadero/falso) que determina si la ruta dada corresponde a un directorio. <br>
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto que contiene la ruta del directorio. <br>

<br>

### <code>libruta.es_archivo(*ruta*)</code>
> Retorna un lógico (verdadero/falso) que determina si la ruta dada corresponde a un archivo. <br>
>
> Argumentos:<br>
> ***ruta***: Una cadena de texto que contiene la ruta del archivo. <br>

<br>
