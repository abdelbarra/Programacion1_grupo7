#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// Necesita buscarEstudiante()
#include "Nicolas.h"

struct Nota{
    int ci;
    float n1,n2,n3;
};

void adicionarNotas()
{
    Nota n;

    cout << "\nCI del estudiante: ";
    cin >> n.ci;

    if(!buscarEstudiante(n.ci, NULL, NULL))
    {
        cout << "\nERROR: El estudiante no existe.\n";
        return;
    }

    cout << "Nota 1: ";
    cin >> n.n1;

    cout << "Nota 2: ";
    cin >> n.n2;

    cout << "Nota 3: ";
    cin >> n.n3;

    ifstream leer("NOTAS.BIN", ios::binary);
    ofstream temp("TEMP.BIN", ios::binary);

    Nota aux;

    while(leer.read((char*)&aux, sizeof(Nota)))
    {
        if(aux.ci != n.ci)
        {
            temp.write((char*)&aux, sizeof(Nota));
        }
    }

    leer.close();

    temp.write((char*)&n, sizeof(Nota));

    temp.close();

    remove("NOTAS.BIN");
    rename("TEMP.BIN", "NOTAS.BIN");

    cout << "\nNotas registradas correctamente.\n";
}