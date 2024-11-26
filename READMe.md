# Link al repositorio
https://github.com/LCrespoG/Finalint3.git

# Cargar y Mostrar Archivos en Consola

## **Descripción del Programa**

Este programa está diseñado para cargar archivos de texto desde el sistema de archivos y, opcionalmente, mostrar su contenido en la consola. Ofrece dos funciones principales para interactuar con los archivos: una que permite especificar el nombre del archivo directamente y otra que solicita al usuario que introduzca el nombre del archivo de forma interactiva.

---

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

---

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

---

## **Casos de Uso**

1. **Cargar un Archivo Existente**:
   - Permite verificar el contenido de un archivo o realizar operaciones adicionales en la memoria con su contenido.

2. **Validación de Archivos**:
   - Útil para asegurarse de que un archivo es accesible antes de utilizarlo en otras partes de un programa más grande.

3. **Manejo Básico de Archivos**:
   - Una forma simple y práctica de interactuar con archivos de texto desde la consola.

---

## **Mensajes Clave del Programa**

- **Éxito**:
  - "El script se ha cargado correctamente en memoria."
- **Error al Abrir un Archivo**:
  - "Error: No se pudo abrir el archivo."
- **Error de Entrada Vacía**:
  - "Error: El nombre del archivo no puede estar vacío."

---

# **Correción**:
Correción de código a Jun Xu Cheng

## Correcion precisa:
1. Problema con la definición de ColorConsole
En el archivo ejercicio.cpp, estás definiendo ColorConsole como una estructura que contiene constantes estáticas. Esto contradice la declaración en el archivo de cabecera ejercicio.h, donde defines los miembros como punteros a char.

Corrección: Asegúrate de que la definición en el archivo de cabecera coincida con la del archivo de implementación. Si usas punteros en el header, necesitas asignarles valores en el archivo .cpp. Por ejemplo:

Corrección en ejercicio.h:

cpp
Copiar código
struct ColorConsole
{
    static const char* fg_blue;
    static const char* bg_white;
};
Corrección en ejercicio.cpp:

cpp
Copiar código
const char* ColorConsole::fg_blue = "\033[34m";
const char* ColorConsole::bg_white = "\033[47m";
2. Uso innecesario de punteros dinámicos (new)
Estás utilizando un puntero dinámico para la instancia de ConsoleBox. Esto puede causar fugas de memoria si olvidas liberar el objeto con delete. Como no parece que necesites usar dinámicamente este objeto, deberías reemplazarlo por una instancia estática o gestionarla con punteros inteligentes (std::unique_ptr o std::shared_ptr).

Corrección: En lugar de usar:

cpp
Copiar código
ConsoleBox* consoleBox = new ConsoleBox;
Usa:

cpp
Copiar código
ConsoleBox consoleBox;
y ajusta las funciones que lo utilizan. Si necesitas un puntero, usa std::unique_ptr:

cpp
Copiar código
#include <memory>

std::unique_ptr<ConsoleBox> consoleBox = std::make_unique<ConsoleBox>();
3. Problemas con el manejo de archivos
En la función load_script, la función fopen y el manejo de archivos son propensos a errores. Es mejor utilizar std::ifstream del estándar moderno de C++ para leer archivos de forma segura.

Corrección: Reemplaza el manejo manual con el uso de std::ifstream:

cpp
Copiar código
#include <fstream>

void load_script(const char* filename, bool show_script = false)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error de apertura de " << filename << std::endl;
        return;
    }

    std::string script((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (show_script)
    {
        std::cout << ColorConsole::fg_blue << ColorConsole::bg_white;
        std::cout << script << std::endl;
    }
    consoleBox.new_text();
    consoleBox.set_text(script);
}
Esto elimina la necesidad de manejar buffers manualmente y reduce los errores por olvido de cerrar el archivo.

4. Uso de scanf y printf en C++
El uso de scanf y printf no es idiomático en C++. Es mejor usar std::cin y std::cout.

Corrección: Reemplaza:

cpp
Copiar código
char filename[500];
printf("Archivo: ");
scanf("%499s", filename);
Por:

cpp
Copiar código
std::string filename;
std::cout << "Archivo: ";
std::cin >> filename;
Esto evita problemas como desbordamientos de buffer.

5. Manejo de excepciones
El bloque try-catch en load_script no es necesario si utilizas las herramientas modernas de C++ como std::ifstream, que no arrojan excepciones por defecto. Además, si decides mantenerlo, es importante que el bloque catch sea más informativo. Por ejemplo:

cpp
Copiar código
catch (const std::exception& e)
{
    std::cerr << "Error durante la lectura del archivo: " << e.what() << std::endl;
}
catch (...)
{
    std::cerr << "Error desconocido durante la lectura del archivo" << std::endl;
}
6. Mejoras generales
Usa #pragma once en lugar de las guardas clásicas (#ifndef, #define). Es más limpio y moderno.
Si ConsoleBox siempre está asociado a load_script, considera encapsularlo en una clase o namespace, en lugar de definirlo como una variable global.
Reorganización sugerida de ejercicio.h:

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

// Funciones para cargar scripts
void load_script(const char* filename, bool show_script = false);
void load_script();
