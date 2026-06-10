// Materia: Programación I, Paralelo 4
// Grupo: 7
// Autor: Abdel Jose Barra Alarcon
//        Alejandro Lima Iriarte
//        Nicolas Valverde Aranibar
// Fecha creación: 27-05-2026
// SISTEMA DE HABILITACION UCB

#include <iostream>

using namespace std;

#include "Nicolas.h"
#include "parte2.h"
#include "Abdel.h"
#include "Alejandro.h"

int main()
{
    int op;

    do
    {
        cout << "\n=================================\n";
        cout << " SISTEMA DE HABILITACION UCB\n";
        cout << "=================================\n";
        cout << "1. Adicionar Estudiante\n";
        cout << "2. Listado de Habilitacion\n";
        cout << "3. Eliminar Estudiante\n";
        cout << "4. Adicionar Notas\n";
        cout << "5. Salir\n";
        cout << "=================================\n";
        cout << "Opcion: ";

        cin >> op;

        switch(op)
        {
            case 1:
                adicionarEstudiante();
                break;

            case 2:
                listadoHabilitacion();
                break;

            case 3:
                eliminarEstudiante();
                break;

            case 4:
                adicionarNotas();
                break;

            case 5:
                cout << "\nPrograma finalizado.\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }

    } while(op != 5);

    return 0;
}