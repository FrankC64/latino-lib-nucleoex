# latino-lib-nucleoex
latino-lib-nucleoex es una extensión para Latino, la cual integra más funciones para expandir las capacidades del lenguaje.

<a name="tabla"></a>
## Tabla de contenidos
* [Tabla de contenidos](#tabla)
    * [Instalación](#instalacion)
        * [Instalación (LAP)](#instalacion_lap)
        * [Instalación manual](#instalacion_manual)
    * [Compilación](#compilacion)
        * [Windows](#windows)
            * [MinGW](#mingw)
            * [Visual Studio](#visual_studio)
        * [Linux](#linux)
    * [Wiki](#wiki)

<a name="instalacion"></a>
## Instalación
Antes de comenzar, debe saber que la instalación **SIN COMPILACIÓN** es exclusivamente para la versión **1.4.0** de Latino en **Windows**, por lo que si usted tiene una versión superior o inferior o se encuentra en un sistema que no sea Windows debe consultar el apartado de [compilación](#compilacion).

<a name="instalacion_lap"></a>
### Instalación (LAP)
El primer método de instalación es a través del administrador de paquetes **LAP**. Antes de continuar debe tener **Python** instalado.

**1-** Instalamos el administrador de paquetes con **pip**.
```Batch
pip install LAP-latino-client
```

**2-** Nos ubicamos en la carpeta donde está nuestro proyecto, en caso contrario la librería será instalada fuera del alcance de Latino.

**3-** Utilizamos **LAP** para instalar la librería.
```Batch
python -m LAP instalar latino-lib-nucleox
```

**4-** En la parte superior de su script de Latino ponga lo siguiente:
```Latino
incluir("libnucleoex")
```

Y ya está todo listo para utilizar la librería.

<a name="instalacion_manual"></a>
### Instalación manual
Aquí se muestra paso a paso la forma de instalar la librería en caso de no tener **Python** o no querer utilizar el administrador de paquetes **LAP**.

**1-** Haga click [aquí](https://github.com/FrankC64/latino-lib-nucleox/releases/latest/download/latino-lib-nucleox.zip) para descargar la última versión.

**2-** Vaya a la carpeta de instalación de Latino y en la subcaperta "bin" extraiga **latino-libnucleoex.dll**.

**3-** En la parte superior de su script de Latino ponga lo siguiente:
```Latino
incluir("libnucleoex")
```

Y ya está todo listo para utilizar la librería.

<a name="compilacion"></a>
## Compilación

<a name="windows"></a>
### Windows

**Requisitos:**
* Tener instalado [cmake](https://cmake.org/download/).
* Tener instalado [git](https://git-scm.com/download/win).
* Tener la siguiente variable de entorno:
    ```
    LATINO_PATH=C:\ruta_de_instalacion_de_latino
    ```
    En caso de no tenerla deberá agregarla en las variables de entorno de Windows.

<a name="mingw"></a>
**Compilación (MinGW):**<br>
Ejecutar lo siguiente en su consola/terminal:

```
git clone https://github.com/FrankC64/latino-lib-nucleoex.git
cd latino-lib-nucleoex
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..\
mingw32-make install
```

<a name="visual_studio"></a>
**Compilación (Visual Studio):**<br>
Ejecutar lo siguiente en su consola/terminal:

```
git clone https://github.com/FrankC64/latino-lib-nucleoex.git
cd latino-lib-nucleoex
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release ..\
cmake --build . --target install --config Release
```

<a name="linux"></a>
### Linux

**Requisitos:**<br>
Antes de comenzar ejecute uno de los siguientes comandos en la terminal dependiendo de su sistema:
* Debian / Ubuntu
    ```Bash
    sudo apt-get install cmake git
    ```
* Arch
    ```Bash
    sudo pacman -S cmake git
    ```
* Fedora / CentOS
    ```Bash
    sudo dnf -y install cmake git
    ```

**Compilación:**<br>
Ejecutar lo siguiente en la terminal:

```
git clone https://github.com/FrankC64/latino-lib-nucleoex.git
cd latino-lib-nucleoex
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
sudo make install
```

<a name="wiki"></a>
## Wiki
Click [aquí](https://github.com/FrankC64/latino-lib-nucleoex/wiki) para conocer las funciones de la librería.

## Preguntas y respuestas
\- **¿Qué es el modo seguro?**<br>
Como actualmente no existe la forma de controlar errores y excepciones en Latino se implementó una funcionalidad para evitar que los errores producidos por la librería detenga el funcionamiento del código y el programador pueda tomar una decisión de qué hacer en caso de que se produzcan estos errores.

\- **¿Cómo compilo la librería para usar el modo seguro de forma predeterminada o forzada?**<br>
Al momento de utilizar el comando **cmake** ponga como instrucción lo siguiente:
```
-DMODO_SEGURO=1
```

en caso de que quiera que por defecto el modo seguro esté habilitado y 

```
-DMODO_SEGURO_FORZADO=1
```

en caso de que desee que el modo seguro esté siempre habilitado y no se pueda modificar desde Latino.

\- **Estoy usando Linux y Latino no carga la librería.**<br>
Si esto le sucede deberá escribir el siguiente comando en su terminal:

```
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
```

Y el problema será solucionado. Si quiere una solución definitiva ejecute el siguiente comando:

```
echo 'export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"' >> ~/.profile
```

Y reinicie su sistema para que se aplique el cambio correctamente.
