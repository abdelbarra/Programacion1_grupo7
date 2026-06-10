#ifndef NOTAS_H
#define NOTAS_H

#include <iostream>
#include <cstring>
#include <fstream> 

using namespace std; 

struct DatosNotas {
    int ci;
    float n1;
    float n2;
    float n3;
};

struct EstudianteEspejo {
    int ci;
    char nombres[30];
    char apellidos[30];
    char materia[30];
    int paralelo;
};

void AdicionarNotasArchivoBinario(string archivoNotasName, string archivoEstudiantesName)
{
    fstream archivoNotas;
    ifstream archivoEstudiantes;
    
    int ciBuscar;
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
            if (est.ci == ciBuscar) {
                carnetExisteEnSistema = true; 
                break;
            }
        }
        archivoEstudiantes.close(); 

        if (!carnetExisteEnSistema) {
            cout << endl <<"Ingrese otro carnet:" << endl << endl;
            system("pause"); 
        }

    } while (!carnetExisteEnSistema); 

    cout << endl <<"Ingrese las calificaciones:" << endl;
    cout << "Ingrese la Evaluacion 1: ";
    cin >> nota1;
    cout << "Ingrese la Evaluacion 2: ";
    cin >> nota2;
    cout << "Ingrese la Evaluacion 3: ";
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
        nuevaNota.ci = ciBuscar;
        nuevaNota.n1 = nota1;
        nuevaNota.n2 = nota2;
        nuevaNota.n3 = nota3;
        
        archivoNotas.write((char*) &nuevaNota, sizeof(DatosNotas));
        cout << endl <<"NOTAS REGISTRADAS" << endl;
    }
    else
    {
        cout << endl <<"NOTAS ACTUALIZADAS" << endl;
    }

    archivoNotas.close();
    system("pause");
}

#endif