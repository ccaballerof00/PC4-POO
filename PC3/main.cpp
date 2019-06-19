#include <iostream>
#include <vector>
#include "Generica.h"
#include "Deque.h"

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


    Matriz<int> matriz2 = Matriz<int>(2,4);
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

    if(matriz1.filas==matriz2.filas && matriz1.columnas == matriz2.columnas)
    {
    Matriz<int> matriz3 = matriz1 + matriz2;
    matriz3.imprimirMatriz();
    }
    else cout<<"No se puede efectuar la suma debido a que las matrices no tienen las mismas dimensiones";
    cout<<endl;

    deque<int> prueba;
    prueba.push_back(5);
    prueba.push_back(1);
    prueba.push_back(4);
    prueba.push_back(8);
    prueba.push_back(2);
    prueba.push_back(4);
    deque<int> resultado;
    resultado =  Hallarminimos(prueba,3);
    imprimirDeque(resultado);



}