# Link al repositorio
https://github.com/LCrespoG/Finalint3.git

# Cargar y Mostrar Archivos en Consola

## **Descripción del Programa**

Este programa está diseñado para cargar archivos de texto desde el sistema de archivos y, opcionalmente, mostrar su contenido en la consola. Ofrece dos funciones principales para interactuar con los archivos: una que permite especificar el nombre del archivo directamente y otra que solicita al usuario que introduzca el nombre del archivo de forma interactiva.


## **Características**

1. **Carga de Archivos**:
   - Lee un archivo de texto desde el disco y almacena su contenido en memoria.
   - Es compatible con cualquier archivo de texto que sea accesible desde el sistema.

2. **Visualización Opcional**:
   - Puede mostrar el contenido del archivo en la consola si se solicita explícitamente.

3. **Interacción con el Usuario**:
   - El programa permite al usuario proporcionar el nombre del archivo de dos formas:
     - Directamente al llamar a la función de carga.
     - Mediante la introducción interactiva del nombre del archivo en la consola.

4. **Manejo de Errores**:
   - Detecta y gestiona problemas comunes, como:
     - Archivos inexistentes.
     - Problemas al abrir el archivo (por ejemplo, falta de permisos).
     - Errores durante la lectura del contenido.


## **Flujo de Uso**

1. **Inicio del Programa**:
   - Si el usuario llama a la función interactiva, el programa solicita que introduzca el nombre de un archivo.

2. **Carga del Archivo**:
   - El programa intenta abrir el archivo especificado.
   - Si el archivo no existe o no se puede abrir, muestra un mensaje de error y termina el proceso.

3. **Lectura del Contenido**:
   - Si el archivo se abre correctamente, se lee su contenido y se almacena en memoria.

4. **Visualización (Opcional)**:
   - Si se solicita, el programa imprime el contenido del archivo en la consola.

5. **Finalización**:
   - Muestra un mensaje de confirmación indicando que el archivo se ha cargado correctamente en memoria.


## **Casos de Uso**

1. **Cargar un Archivo Existente**:
   - Permite verificar el contenido de un archivo o realizar operaciones adicionales en la memoria con su contenido.

2. **Validación de Archivos**:
   - Útil para asegurarse de que un archivo es accesible antes de utilizarlo en otras partes de un programa más grande.

3. **Manejo Básico de Archivos**:
   - Una forma simple y práctica de interactuar con archivos de texto desde la consola.


## **Mensajes Clave del Programa**

- **Éxito**:
  - "El script se ha cargado correctamente en memoria."
- **Error al Abrir un Archivo**:
  - "Error: No se pudo abrir el archivo."
- **Error de Entrada Vacía**:
  - "Error: El nombre del archivo no puede estar vacío."


# **Correción**:
Correción de código a Jun Xu Cheng

## Correcion precisa:
# Correcciones en el Código

## **main.cpp**
Sin cambios, está bien estructurado.

```cpp
#include "EJ1/Ejercicio.h"

int main()
{
    load_script();
    return 0;
}
```
ejercicio.h
Cambiado #ifndef por #pragma once para simplificar las guardas.
Definiciones de ColorConsole actualizadas para ser consistentes.
cpp
Copiar código
#pragma once

#include <iostream>
#include <string>

// ColorConsole
struct ColorConsole
{
    static const char* fg_blue;
    static const char* bg_white;
};

// ConsoleBox
struct ConsoleBox
{
    void new_text();
    void set_text(const std::string& text);
};

extern ConsoleBox consoleBox;

// Funciones para cargar scripts
void load_script(const char* filename, bool show_script = false);
void load_script();
```
ejercicio.cpp
Uso de std::ifstream en lugar de FILE*.
Eliminado el puntero dinámico para consoleBox, ahora es una instancia estática.
Uso de std::string en lugar de scanf para leer el nombre del archivo.
Añadida inicialización correcta para ColorConsole.

```cpp
Copiar código
#include <iostream>
#include <fstream>
#include "Ejercicio.h"

// Inicialización de los colores
const char* ColorConsole::fg_blue = "\033[34m";
const char* ColorConsole::bg_white = "\033[47m";

// Instancia global de ConsoleBox
ConsoleBox consoleBox;

void load_script(const char* filename, bool show_script)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error al abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    if (show_script)
    {
        std::cout << ColorConsole::fg_blue << ColorConsole::bg_white;
        std::cout << script << std::endl;
    }

    consoleBox.new_text();
    consoleBox.set_text(script);
}

void load_script()
{
    std::string filename;
    std::cout << "Archivo: ";
    std::cin >> filename;
    load_script(filename.c_str(), true);
}
```
