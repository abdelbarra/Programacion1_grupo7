// Materia: Programación I, Paralelo 4
// Grupo: 7
// Autor: Abdel Jose Barra Alarcon
//        Alejandro Lima Iriarte
//        Nicolas Valverde Aranibar
// Fecha creación: 27-05-2026
// SISTEMA DE HABILITACION UCB 

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

bool buscarEstudiante(int ciBuscado, char nomBuscado[], char apeBuscado[]);
void adicionarEstudiante();
void adicionarNotas();
bool buscarNota(int ci, Nota &n);
void listadoHabilitacion();
void eliminarEstudiante();

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
        switch(op){
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
    }while(op != 5);
    return 0;
}
//--------------------------------------------------
// FUNCION BUSCAR ESTUDIANTE
//--------------------------------------------------
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
            if(strcmp(p.nombres,nomBuscado)==0 && strcmp(p.apellidos,apeBuscado)==0)
            {
                archivo.close();
                return true;
            }
        }
    }
    archivo.close();
    return false;
}
//--------------------------------------------------
// ADICIONAR ESTUDIANTE
//--------------------------------------------------
void adicionarEstudiante()
{
    Postulante p;
    cout << "\nCI: ";
    cin >> p.ci;
    if(buscarEstudiante(p.ci,NULL,NULL))
    {
        cout << "\nERROR: CI repetido.\n";
        return;
    }
    cin.ignore();
    cout << "Nombres: ";
    cin.getline(p.nombres,30);
    cout << "Apellidos: ";
    cin.getline(p.apellidos,30);
    if(buscarEstudiante(-1, p.nombres, p.apellidos)){
        cout << "\nERROR: Nombre y apellido repetidos.\n";
        return;
    }
    cout << "Materia: ";
    cin.getline(p.materia,30);
    cout << "Paralelo: ";
    cin >> p.paralelo;
    ofstream archivo("ESTUDIANTES.BIN", ios::binary|ios::app);
    archivo.write((char*)&p, sizeof(Postulante));
    archivo.close();
    cout << "\nEstudiante registrado correctamente.\n";
}
//--------------------------------------------------
// ADICIONAR NOTAS
//--------------------------------------------------
void adicionarNotas()
{
    Nota n;
    cout << "\nCI del estudiante: ";
    cin >> n.ci;
    if(!buscarEstudiante(n.ci,NULL,NULL))
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
//--------------------------------------------------
// BUSCAR NOTA
//--------------------------------------------------
bool buscarNota(int ci, Nota &n){
    ifstream archivo("NOTAS.BIN", ios::binary);
    while(archivo.read((char*)&n, sizeof(Nota))){
        if(n.ci == ci)
        {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}
//--------------------------------------------------
// LISTADO DE HABILITACION
//--------------------------------------------------
void listadoHabilitacion(){
    ifstream archivo("ESTUDIANTES.BIN", ios::binary);
    Postulante p;
    Nota n;
    float sumaPromedios = 0;
    int cantidad = 0;
    cout << "\n============================================================================================\n";
    cout << left << setw(10) << "CI" << setw(15) << "NOMBRES" << setw(15) << "APELLIDOS" << setw(20) << "MATERIA" << setw(10) << "PARALELO" << setw(15) << "PROMEDIO" << setw(20) << "ESTADO" << endl;
    cout << "===============================================================================================\n";
    while(archivo.read((char*)&p, sizeof(Postulante))){
        if(buscarNota(p.ci,n)){
            float promedio = (n.n1+n.n2+n.n3)/3;
            string estado;
            if(n.n1>=60 && n.n2>=60 && n.n3>=60){
                estado = "HABILITADO";
            }
            else
            {
                estado = "NO HABILITADO";
            }
            cout << left << setw(10) << p.ci << setw(15) << p.nombres << setw(15) << p.apellidos << setw(20) << p.materia << setw(10) << p.paralelo << setw(15) << fixed << setprecision(2) << promedio << setw(20) << estado << endl;
            sumaPromedios += promedio;
            cantidad++;
        }
    }
    archivo.close();
    cout << "===============================================================================================\n";
    if(cantidad > 0)
    {
        cout << "\nPROMEDIO GENERAL DEL CURSO: " << fixed << setprecision(2) << sumaPromedios/cantidad << endl;
    }
    else
    {
        cout << "\nNo existen notas registradas.\n";
    }
}

//--------------------------------------------------
// ELIMINAR ESTUDIANTE
//--------------------------------------------------

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