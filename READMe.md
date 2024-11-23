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
