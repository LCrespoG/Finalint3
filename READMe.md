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

- Carga de scripts (50 puntos)
- load_script(const char* filename, bool show_script = false) (25 puntos):

**Errores:**

No verifica si el tamaño total del archivo excede los límites de la memoria al construir script. Esto puede causar un desbordamiento si se leen archivos grandes.
Usa una función obsoleta como fopen, que puede reemplazarse con alternativas modernas más seguras (std::ifstream).
El manejo de cadenas con char buf[4001] es propenso a errores. Es mejor usar clases de C++ como std::vector<char> para gestionar buffers dinámicamente.

**Corrección sugerida:**

Utilizar std::ifstream en lugar de fopen para mayor claridad y seguridad.
Agregar un límite explícito para el tamaño del archivo cargado.

- load_script() (25 puntos):

**Errores:**

Usa scanf, que puede ser reemplazado por std::cin para evitar problemas de formato o sobrelectura.
Falta manejo de entradas inválidas del usuario, como rutas vacías o nombres de archivo con caracteres no permitidos.

**Corrección sugerida:**

Cambiar scanf por std::getline con validaciones adicionales para el formato del archivo.

- Manejo de errores (50 puntos)
- Nombre del archivo no existe (15 puntos):

**Errores:**

Solo imprime un mensaje de error en caso de fallo al abrir el archivo, pero no proporciona detalles adicionales (como errno o la descripción del error).

**Corrección sugerida:**

Usar std::cerr con información detallada del error (strerror(errno)).
- Archivo no se puede abrir (15 puntos):

**Errores:**

El manejo de errores en fopen es adecuado, pero puede mejorarse con un mensaje más descriptivo.

**Corrección sugerida:**

Imprimir un mensaje más claro que incluya posibles causas del problema, como permisos insuficientes o archivo inexistente.
Error durante la lectura del archivo (20 puntos):

**Errores:**

El catch (...) es demasiado genérico y no informa del tipo de error que ocurrió.
No se limpia completamente el estado de consoleBox en caso de errores.

**Corrección sugerida:**

Usar excepciones específicas (std::ios_base::failure) y añadir limpieza explícita de recursos.
Código Corregido

## Código corregido:

main.cpp
```cpp
Copiar código
#include "EJ1/Ejercicio.h"

int main()
{
    load_script();
    return 0;
}
```
ejercicio.cpp
```cpp
Copiar código
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <cstring>

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() { std::cout << "New console text initialized.\n"; }
    void set_text(const std::string &text) { std::cout << text << std::endl; }
};

ConsoleBox *consoleBox = new ConsoleBox;

void load_script(const char* filename, bool show_script = false)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << "Error opening file '" << filename << "': " << strerror(errno) << std::endl;
        return;
    }

    try
    {
        file.seekg(0, std::ios::end);
        std::size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (file_size > 10 * 1024 * 1024) // Limitar a 10 MB
        {
            throw std::runtime_error("File size exceeds 10 MB limit.");
        }

        std::vector<char> buffer(file_size);
        file.read(buffer.data(), file_size);

        if (file.fail())
        {
            throw std::ios_base::failure("Error reading file.");
        }

        std::string script(buffer.begin(), buffer.end());
        if (show_script)
        {
            std::cout << ColorConsole::fg_blue << ColorConsole::bg_white << script << std::endl;
        }
        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void load_script()
{
    std::cout << "Archivo: ";
    std::string filename;
    std::getline(std::cin, filename);

    if (filename.empty())
    {
        std::cerr << "No se proporcionó un nombre de archivo válido." << std::endl;
        return;
    }

    load_script(filename.c_str(), true);
}
```
ejercicio.h

Sin cambios significativos, pero se actualiza la firma de las funciones y se mantiene la declaración estructurada.
