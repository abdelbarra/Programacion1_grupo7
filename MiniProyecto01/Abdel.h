#ifndef ELIMINAR_ESTUDIANTE_H
#define ELIMINAR_ESTUDIANTE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Estructura de almacenamiento de estudiantes
struct EstudianteEspejo {
    int ci;
    char nombres[30];
    char apellidos[30];
    char materia[30];
    int paralelo;
};

// Limpieza del flujo de entrada
void limpiarEntrada() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Inicio del modulo de eliminacion de estudiantes
void eliminarEstudiante() {
    cout << "\n--------------------------------------------------------------------------------" << endl;
    cout << "     Modulo De Eliminacion De Estudinte super ultra mega sayayin 100/ confiable" << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    int ciBorrar;

    // Solicitud del CI del estudiante
    cout << "--> Ingrese el CI del estudiante: ";

    // Validacion de entrada numerica para el CI
    while (!(cin >> ciBorrar)) {
        cout << " ! Error: El CI debe ser un numero entero, intente de nuevo: ";
        limpiarEntrada();
    }

    // Apertura del archivo de estudiantes
    std::ifstream archivoEntrada("ESTUDIANTES.BIN", std::ios::binary);

    // Verificacion de existencia del archivo
    if (!archivoEntrada) {
        cout << "\n ! No existe el archivo ESTUDIANTES.BIN" << endl;
        return;
    }

    // Almacenamiento temporal de registros conservados
    vector<EstudianteEspejo> estudiantes;

    // Variable auxiliar para lectura de registros
    EstudianteEspejo estudiante;

    // Indicador de existencia del estudiante
    bool encontrado = false;

    // Lectura completa del archivo binario
    while (archivoEntrada.read(
        reinterpret_cast<char*>(&estudiante),
        sizeof(EstudianteEspejo)))
    {
        // Comparacion del CI ingresado con el registro actual
        if (estudiante.ci == ciBorrar) {
            encontrado = true;
        }
        else {
            // Conservacion de registros distintos al estudiante eliminado
            estudiantes.push_back(estudiante);
        }
    }

    // Cierre del archivo de lectura
    archivoEntrada.close();

    // Verificacion de existencia del estudiante
    if (!encontrado) {
        cout << "\n No existe un estudiante con el CI "
             << ciBorrar << endl;
        return;
    }

    char decision;

    // Solicitud de confirmacion de eliminacion
    cout << "\n Confirmar eliminacion de el perro estudiante: (S/N): ";
    cin >> decision;

    // Cancelacion de la operacion
    if (std::toupper(decision) != 'S') {
        cout << "\n[x] Operacion cancelada." << endl;
        return;
    }

    // Apertura del archivo para reescritura
    std::ofstream archivoSalida(
        "ESTUDIANTES.BIN",
        std::ios::binary | std::ios::trunc
    );

    // Verificacion de apertura del archivo
    if (!archivoSalida) {
        cout << "\n ! Error al abrir el archivo." << endl;
        return;
    }

    // Escritura de registros conservados
    for (const auto& est : estudiantes) {
        archivoSalida.write(
            reinterpret_cast<const char*>(&est),
            sizeof(EstudianteEspejo)
        );
    }

    // Cierre del archivo de escritura
    archivoSalida.close();

    // Confirmacion de eliminacion exitosa
    cout << "\n Estudiante eliminado correctamente----> :D" << endl;
    cout << "==========================================" << endl;
}

#endif