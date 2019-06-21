#include <iostream>
#include <vector>
#include "Generica.h"
#include "Concurrente.h"
#include <ctime>
using namespace std;


int main() {
    M<int> matriz1 =M<int>(2,3);
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            matriz1.AnadirElemento(2,i,j);
        }
    }
    matriz1.imprimirMatriz();
    cout<<endl;


    M<int> matriz2 = M<int>(3,4);
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            matriz2.AnadirElemento(3,i,j);
        }
    }
//
   matriz2.imprimirMatriz();
    cout<<endl;


    unsigned t0, t1;
    try {
        t0=clock();
        M<int> matriz3 = matriz1 ^ matriz2;
        t1=clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout<< "Tiempo de ejecución:"<<time<<endl;
        matriz3.imprimirMatriz();
    }
    catch (exception& e)
    {
        cout<<e.what();
    }

    Matriz<int> matriz4 =Matriz<int>(3,4);
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            matriz4.AnadirElemento(5,i,j);
        }
    }
    matriz4.imprimirMatriz();
    cout<<endl;


    Matriz<int> matriz5 = Matriz<int>(4,4);
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            matriz5.AnadirElemento(1,i,j);
        }
    }
//
    matriz5.imprimirMatriz();
    cout<<endl;

    Matriz<int>matriz6=matriz4*matriz5;
    //matriz6.imprimirMatriz();
}