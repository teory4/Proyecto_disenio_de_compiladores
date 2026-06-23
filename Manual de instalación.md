# Instalación del Compilador MiniCalc

## Requisitos del Sistema

Para ejecutar el compilador MiniCalc se requiere:

* Sistema operativo Windows, Linux o macOS.
* Visual Studio Code.
* Extensión C/C++ para Visual Studio Code.
* Compilador GNU G++ con soporte para C++11 o superior.
* Conexión a Internet para descargar el proyecto.

## Descarga del Proyecto

El código fuente del compilador se encuentra disponible en el repositorio oficial de GitHub:

[Proyecto Diseño de Compiladores](https://github.com/teory4/Proyecto_disenio_de_compiladores.git?utm_source=chatgpt.com)

El repositorio puede descargarse mediante Git utilizando el siguiente comando:

```text
git clone https://github.com/teory4/Proyecto_disenio_de_compiladores.git
```

También es posible descargar el proyecto en formato ZIP desde GitHub y posteriormente descomprimirlo en una carpeta local.

## Apertura del Proyecto

Una vez descargado el repositorio, abrir Visual Studio Code y seleccionar:

```text
Archivo → Abrir carpeta
```

Posteriormente seleccionar la carpeta:

```text
Proyecto_disenio_de_compiladores
```

## Compilación

Abrir la terminal integrada de Visual Studio Code y ejecutar:

```text
g++ compilador.cpp -o compilador
```

Si la compilación finaliza correctamente se generará el archivo ejecutable denominado:

```text
compilador
```

o

```text
compilador.exe
```

dependiendo del sistema operativo utilizado.

## Ejecución

Ejecutar el compilador mediante:

### Linux / macOS

```text
./compilador
```

### Windows

```text
compilador.exe
```

## Verificación de la Instalación

Si la instalación se realizó correctamente, el programa mostrará en consola los resultados correspondientes a:

* Análisis léxico.
* Análisis sintáctico.
* Análisis semántico.
* Generación de código intermedio.

Además, en caso de existir errores en el programa MiniCalc analizado, estos serán reportados en la fase correspondiente.
