## Ingreso de Programas MiniCalc

El compilador MiniCalc procesa los programas escritos por el usuario a través de una cadena de texto almacenada en la variable denominada `codigo`, ubicada dentro de la función principal (`main`) del programa.

Para analizar un nuevo programa, el usuario debe modificar únicamente el contenido de dicha variable respetando la sintaxis definida por el lenguaje MiniCalc.

**Ejemplo:**

```cpp
string codigo = R"(

declarar x = 2;
declarar y = 3;
declarar res = 0;

mientras(x < 6){

    si(x % 2 == 0){

        res = res + potencia(x,y);
    }

    x = x + 1;
}

imprimir res;

)";
```

Una vez reemplazado el contenido de la variable `codigo` por el programa deseado, el usuario deberá guardar los cambios, compilar nuevamente el proyecto y ejecutar el compilador.

## Flujo de Ejecución

Cada vez que se ejecuta el compilador, se realizan automáticamente las siguientes etapas:

1. Análisis léxico.
2. Análisis sintáctico.
3. Análisis semántico.
4. Generación de código intermedio mediante cuádruplos.

Si durante alguna de estas etapas se detectan errores, el sistema mostrará los mensajes correspondientes en la consola.

## Resultados Generados

Al finalizar la ejecución, el compilador puede mostrar:

* Lista de tokens reconocidos por el analizador léxico.
* Confirmación de análisis sintáctico válido.
* Confirmación de análisis semántico válido.
* Reporte de errores léxicos, sintácticos o semánticos cuando existan.
* Código intermedio representado mediante cuádruplos.

## Consideraciones de Uso

Para que un programa MiniCalc sea aceptado correctamente, se deben cumplir las siguientes condiciones:

* Toda variable debe declararse antes de ser utilizada.
* No se permite redeclarar una variable existente.
* Las funciones matemáticas deben recibir la cantidad correcta de parámetros.
* Los operadores relacionales solamente pueden utilizarse dentro de estructuras de control como `si` y `mientras`.
* Las instrucciones deben respetar la gramática formal definida para MiniCalc.

El incumplimiento de cualquiera de estas reglas producirá errores que serán reportados por la fase correspondiente del compilador.
