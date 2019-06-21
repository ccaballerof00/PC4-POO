//
// Created by fabrizio on 6/21/19.
//

#ifndef PC3_GENERICA_H
#define PC3_GENERICA_H

#include<vector>
#include <iostream>

using namespace std;


template<typename T1>
class M
{
public:
    int filas;
    int columnas;
    vector<vector<T1>> matriz;
    M(int filas, int columnas):filas{filas},columnas{columnas}
    {
        for(int i=0;i<filas;i++)
        {
            vector<T1> a;
            for(int j=0;j<columnas;j++){
                a.push_back(0);
            }
            matriz.push_back(a);
        }
    }
    void AnadirElemento(T1 a,int x,int y);
    void imprimirMatriz();
    M<T1> operator ^ (M<T1> m);

};

template<typename T1>
void M<T1>::AnadirElemento(T1 a,int x, int y)
{

    matriz[x][y]=a;
}


template<typename T1>
void M<T1>::imprimirMatriz()
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
M<T1> M<T1>::operator ^ (M<T1> m)
{
    int i,j,z;
    if(columnas == m.filas )
    {
        int sum=0;
        M<T1> resultado = M<T1>(filas,m.columnas);
        for(i=0; i<filas; ++i) {
            for (j = 0; j < m.columnas; ++j) {


                for (z = 0 ; z < columnas; ++z) {
                    sum += matriz[i][z] * m.matriz[z][j];
                }

                resultado.AnadirElemento(sum,i,j);
                sum=0;
            }
        }
        return resultado;
    }
    else
        throw runtime_error("No se puede hacer la multiplicación");

}





#endif //PC3_GENERICA_H
