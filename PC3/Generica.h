//
// Created by cristian on 6/7/19.
//

#ifndef PC3_GENERICA_H
#define PC3_GENERICA_H
#include<vector>
#include <iostream>

using namespace std;


template<typename T1>
class Matriz
{
public:
    int filas;
    int columnas;
    vector<vector<T1>> matriz;
    Matriz(int filas, int columnas):filas{filas},columnas{columnas}
    {
        for(int i=0;i<filas;i++)
        {
            vector<T1> a;
            matriz.push_back(a);
        }
    }
    void AnadirElemento(T1 a);
    void imprimirMatriz();
    Matriz<T1> operator * (Matriz<T1> m);

};

template<typename T1>
void Matriz<T1>::AnadirElemento(T1 a)
{
    for(int i=0;i<filas;i++)
    {
        if(matriz.at(i).size()<columnas)
        {
            matriz.at(i).push_back(a);
            break;
        }
    }
}


template<typename T1>
void Matriz<T1>::imprimirMatriz()
{
    for(int i=0;i<filas;i++)
    {
        for(int j=0;j<columnas;j++)
        {
            std::cout<<matriz.at(i).at(j)<<" ";
        }
        std::cout<<endl;
    }
}


template<typename T1>
Matriz<T1> Matriz<T1>::operator * (Matriz<T1> m)
        {
            if(columnas == m.filas )
            {
                int sum=0;
                Matriz<T1> resultado = Matriz<T1>(filas,m.columnas);
                for(int i=0; i<filas; ++i) {
                    for (int j = 0; j < m.columnas; ++j) {


                        for (int z = 0 ; z < columnas; ++z) {
                            sum += matriz[i][z] * m.matriz[z][j];
                        }

                        resultado.AnadirElemento(sum);
                        sum=0;
                    }
                }
                return resultado;
            }
            else
                throw runtime_error("No se puede hacer la multiplicación");

        }


#endif //PC3_GENERICA_H
