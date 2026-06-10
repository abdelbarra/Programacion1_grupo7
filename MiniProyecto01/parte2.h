#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Nota{
    int ci;
    float n1,n2,n3;
};

bool buscarNota(int ci, Nota &n)
{
    ifstream archivo("NOTAS.BIN", ios::binary);

    while(archivo.read((char*)&n, sizeof(Nota)))
    {
        if(n.ci == ci)
        {
            archivo.close();
            return true;
        }
    }

    archivo.close();
    return false;
}

void listadoHabilitacion()
{
    ifstream archivo("ESTUDIANTES.BIN", ios::binary);

    Postulante p;
    Nota n;

    float sumaPromedios = 0;
    int cantidad = 0;

    cout << "\n============================================================================================\n";

    cout << left
         << setw(10) << "CI"
         << setw(15) << "NOMBRES"
         << setw(15) << "APELLIDOS"
         << setw(20) << "MATERIA"
         << setw(10) << "PARALELO"
         << setw(15) << "PROMEDIO"
         << setw(20) << "ESTADO"
         << endl;

    cout << "============================================================================================\n";

    while(archivo.read((char*)&p, sizeof(Postulante)))
    {
        if(buscarNota(p.ci, n))
        {
            float promedio = (n.n1 + n.n2 + n.n3) / 3;

            string estado;

            if(n.n1 >= 60 && n.n2 >= 60 && n.n3 >= 60)
            {
                estado = "HABILITADO";
            }
            else
            {
                estado = "NO HABILITADO";
            }

            cout << left
                 << setw(10) << p.ci
                 << setw(15) << p.nombres
                 << setw(15) << p.apellidos
                 << setw(20) << p.materia
                 << setw(10) << p.paralelo
                 << setw(15) << fixed << setprecision(2) << promedio
                 << setw(20) << estado
                 << endl;

            sumaPromedios += promedio;
            cantidad++;
        }
    }

    archivo.close();

    cout << "============================================================================================\n";

    if(cantidad > 0)
    {
        cout << "\nPROMEDIO GENERAL DEL CURSO: "
             << fixed << setprecision(2)
             << sumaPromedios / cantidad << endl;
    }
    else
    {
        cout << "\nNo existen notas registradas.\n";
    }
}