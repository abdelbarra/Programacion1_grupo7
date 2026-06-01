//Materia:programacion 1,Paralelo4
//Autor: Abdel JOse Barra Alarcon
//Carnet: 13828347
//Fecha de creacion: 04/03/2026
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
int Numerorandom(){
    srand(time(NULL));
    int random=0;
    random= rand()%(50-20)+20;
    return random;

}
int main(){
    int n,descuento=0,sprecios,preciototal=0;
    const float iva=0.13;
    cout<<"ingrese la cantidad de productos: ";
    cin>>n;
    for (int i = 1; i <=n; i++){
        sprecios=sprecios+Numerorandom();
        cout<<Numerorandom;
        cout<<sprecios<<endl;
    }
    preciototal=sprecios-(sprecios*0.05);
    if (sprecios>=2500){
        cout<<"la suma de los precios de los productos es mayor a 2500, se aplica un descuemto del 5%"<<endl;
        cout<<"su precio original es: "<<sprecios<<endl<<"su precio con desuento es: "<<preciototal<<" y su iva a pagar es de: "<<preciototal*iva<<endl;
    }
    else{
        cout<<"la suma de sus precios es menor a 2500, no se aplicara descuento";
        cout<<"La suma de sus precios es: "<<sprecios<<" su iva a pagar es: "<<sprecios*iva<<endl;
    }
    return 0;
}