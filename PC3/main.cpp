#include <iostream>
#include <vector>
#include "Generica.h"
#include <ctime>

using namespace std;


int main() {
    Matriz<int> matriz1 =Matriz<int>(2,3);
    matriz1.AnadirElemento(1);
    matriz1.AnadirElemento(2);
    matriz1.AnadirElemento(3);
    matriz1.AnadirElemento(4);
    matriz1.AnadirElemento(1);
    matriz1.AnadirElemento(9);
    matriz1.imprimirMatriz();
    cout<<endl;


    Matriz<int> matriz2 = Matriz<int>(3,4);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);
    matriz2.AnadirElemento(5);

    matriz2.imprimirMatriz();
    cout<<endl;


    unsigned t0, t1;
    try {
        t0=clock();
        Matriz<int> matriz3 = matriz1 * matriz2;
        t1=clock();
        double time = (double(t1-t0)/CLOCKS_PER_SEC);
        cout<< "Tiempo de ejecución:"<<time<<endl;
        matriz3.imprimirMatriz();
    }
    catch (exception& e)
    {
        cout<<e.what();
    }

}