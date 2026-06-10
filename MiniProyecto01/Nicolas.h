#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Postulante{
    int ci;
    char nombres[30];
    char apellidos[30];
    char materia[30];
    int paralelo;
};

bool buscarEstudiante(int ciBuscado, char nomBuscado[], char apeBuscado[])
{
    ifstream archivo("ESTUDIANTES.BIN", ios::binary);

    Postulante p;

    while(archivo.read((char*)&p, sizeof(Postulante)))
    {
        if(ciBuscado != -1 && p.ci == ciBuscado)
        {
            archivo.close();
            return true;
        }

        if(nomBuscado != NULL && apeBuscado != NULL)
        {
            if(strcmp(p.nombres, nomBuscado) == 0 &&
               strcmp(p.apellidos, apeBuscado) == 0)
            {
                archivo.close();
                return true;
            }
        }
    }

    archivo.close();
    return false;
}

void adicionarEstudiante()
{
    Postulante p;

    cout << "\nCI: ";
    cin >> p.ci;

    if(buscarEstudiante(p.ci, NULL, NULL))
    {
        cout << "\nERROR: CI repetido.\n";
        return;
    }

    cin.ignore();

    cout << "Nombres: ";
    cin.getline(p.nombres, 30);

    cout << "Apellidos: ";
    cin.getline(p.apellidos, 30);

    if(buscarEstudiante(-1, p.nombres, p.apellidos))
    {
        cout << "\nERROR: Nombre y apellido repetidos.\n";
        return;
    }

    cout << "Materia: ";
    cin.getline(p.materia, 30);

    cout << "Paralelo: ";
    cin >> p.paralelo;

    ofstream archivo("ESTUDIANTES.BIN", ios::binary | ios::app);

    archivo.write((char*)&p, sizeof(Postulante));

    archivo.close();

    cout << "\nEstudiante registrado correctamente.\n";
}