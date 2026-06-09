#ifndef NOTAS_H
#define NOTAS_H

#include <iostream>
#include <cstring>
#include <fstream> 

using namespace std; 

struct DatosNotas {
    char ci[15];
    float n1;
    float n2;
    float n3;
};

struct EstudianteEspejo {
    char ci[15];
    char nombres[50];
    char apellidos[50];
    bool activo; 
};

void AdicionarNotasArchivoBinario(string archivoNotasName, string archivoEstudiantesName)
{
    fstream archivoNotas;
    ifstream archivoEstudiantes;
    
    string ciBuscar;
    float nota1, nota2, nota3;
    bool carnetExisteEnSistema = false;

    do {
        system("cls"); 
        cout << "ADICIONAR NOTAS DE HABILITACION " << endl;
        cout << "===============================" << endl;
        
        cout << "Ingrese el CI del estudiante: "; 
        cin >> ciBuscar;

        archivoEstudiantes.open(archivoEstudiantesName, ios::binary);
        
        if (!archivoEstudiantes) {
            cout << endl <<"Error: El archivo de estudiantes no existe." << endl;
            system("pause");
            return;
        }

        EstudianteEspejo est;
        carnetExisteEnSistema = false;

        while (archivoEstudiantes.read((char*) &est, sizeof(EstudianteEspejo))) {
            if (est.activo && est.ci == ciBuscar) {
                carnetExisteEnSistema = true; 
                break;
            }
        }
        archivoEstudiantes.close(); 

        if (!carnetExisteEnSistema) {
            cout << endl <<"El usuario no existe o esta dado de baja. Intente con otro carnet." << endl << endl;
            system("pause"); 
        }

    } while (!carnetExisteEnSistema); 

    cout << endl <<"Estudiante verificado correctamente. Ingrese las calificaciones:" << endl;
    cout << "Ingrese la Evaluacion Continua 1: ";
    cin >> nota1;
    cout << "Ingrese la Evaluacion Continua 2: ";
    cin >> nota2;
    cout << "Ingrese la Evaluacion Continua 3: ";
    cin >> nota3;

    archivoNotas.open(archivoNotasName, ios::in | ios::out | ios::binary);

    if (!archivoNotas) {
        archivoNotas.open(archivoNotasName, ios::out | ios::binary);
        archivoNotas.close();
        archivoNotas.open(archivoNotasName, ios::in | ios::out | ios::binary);
    }

    DatosNotas notasPersona;
    bool notaEncontrada = false;

    while (archivoNotas.read((char*) &notasPersona, sizeof(DatosNotas)))
    {
        if (notasPersona.ci == ciBuscar)
        {
            archivoNotas.seekp(archivoNotas.tellg(), ios::beg);
            archivoNotas.seekp(-sizeof(DatosNotas), ios::cur);
            
            notasPersona.n1 = nota1;
            notasPersona.n2 = nota2;
            notasPersona.n3 = nota3;
            
            archivoNotas.write((char*) &notasPersona, sizeof(DatosNotas));
            notaEncontrada = true;
            break; 
        }
    }

    if (!notaEncontrada)
    {
        archivoNotas.clear(); 
        archivoNotas.seekp(0, ios::end); 
        
        DatosNotas nuevaNota;
        strncpy(nuevaNota.ci, ciBuscar.c_str(), 15);
        nuevaNota.n1 = nota1;
        nuevaNota.n2 = nota2;
        nuevaNota.n3 = nota3;
        
        archivoNotas.write((char*) &nuevaNota, sizeof(DatosNotas));
        cout << endl <<"NOTAS REGISTRADAS POR PRIMERA VEZ EN EL ARCHIVO." << endl;
    }
    else
    {
        cout << endl <<"NOTAS ACTUALIZADAS (SE BORRARON LAS ANTERIORES SATISFACTORIAMENTE)." << endl;
    }

    archivoNotas.close();
    system("pause");
}
#endif