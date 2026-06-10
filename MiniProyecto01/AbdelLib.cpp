#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Postulante{
    int ci;
    char nombres[30];
    char apellidos[30];
    char materia[30];
    int paralelo;
};

struct Nota{
    int ci;
    float n1,n2,n3;
};

void eliminarEstudiante()
{
    int ci;
    cout << "\nCI a eliminar: ";
    cin >> ci;
    ifstream leer("ESTUDIANTES.BIN", ios::binary);
    ofstream temp("TEMP.BIN", ios::binary);
    Postulante p;

    while(leer.read((char*)&p, sizeof(Postulante)))
    {
        if(p.ci != ci)
        {
            temp.write((char*)&p, sizeof(Postulante));
        }
    }

    leer.close();
    temp.close();

    remove("ESTUDIANTES.BIN");
    rename("TEMP.BIN", "ESTUDIANTES.BIN");
    ifstream leer2("NOTAS.BIN", ios::binary);
    ofstream temp2("TEMP.BIN", ios::binary);

    Nota n;
    while(leer2.read((char*)&n, sizeof(Nota)))
    {
        if(n.ci != ci)
        {
            temp2.write((char*)&n, sizeof(Nota));
        }
    }
    leer2.close();
    temp2.close();
    remove("NOTAS.BIN");
    rename("TEMP.BIN", "NOTAS.BIN");
    cout << "\nEstudiante eliminado correctamente.\n";
}