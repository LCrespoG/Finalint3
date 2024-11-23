#include "cargararchivo.h"

#include <iostream>
#include <fstream>
#include <string>

void load_script(const char* filename, bool show_script = false) {
    std::ifstream file(filename, std::ios::in);
    if (!file) {
        std::cerr << "Error: No se pudo abrir el archivo '" << filename << "'." << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();

    if (show_script) {
        std::cout << "Contenido del archivo:" << std::endl;
        std::cout << content << std::endl;
    }

    // Simulación de cargar el script
    std::cout << "El script se ha cargado correctamente en memoria." << std::endl;
}

void load_script() {
    std::string filename;
    std::cout << "Ingrese el nombre del archivo: ";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        std::cerr << "Error: El nombre del archivo no puede estar vacío." << std::endl;
        return;
    }

    load_script(filename.c_str(), true);
}