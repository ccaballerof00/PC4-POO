//
// Created by fabrizio on 6/21/19.
//

#ifndef PC3_CONCURRENTE_H
#define PC3_CONCURRENTE_H


//
// Created by fabrizio on 6/21/19.
//

#include<vector>
#include <iostream>
#include <sys/time.h>
#define NUM_HILOS 2
using namespace std;

//template <typename T>
vector<vector<int>> matriz1;
//template <typename T>
vector<vector<int>> matriz2;
//template <typename T>
vector<vector<int>> matriz3;


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
            for(int j=0;j<columnas;j++){
                a.push_back(0);
            }
            matriz.push_back(a);
        }
    }
    void AnadirElemento(T1 a,int x,int y);
    void imprimirMatriz();
    Matriz<T1> operator * (Matriz<T1> m);

};

template<typename T1>
void Matriz<T1>::AnadirElemento(T1 a,int x, int y)
{

    matriz[x][y]=a;
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

struct datos {
    long thread_id;
    int num_filas1;
    int num_columnas1;
    int num_filas2;
    int num_columnas2;
};

struct datos datos_pasar[NUM_HILOS];



void* multiplicar_paralelo(void* parametros) {
   // cout<<"hola"<<endl;
    int j, filas1, columnas1, r, filas2, columnas2,z;
    long i, lim_inf, lim_sup, k;
    long t;
    struct datos* mis_datos;
    mis_datos=(struct datos*)parametros;
    t = mis_datos->thread_id;
    filas1 = mis_datos->num_filas1;
    columnas1 = mis_datos->num_columnas1;
    filas2 = mis_datos->num_filas2;
    columnas2 = mis_datos->num_columnas2;

    if(filas1%NUM_HILOS != 0 && t==NUM_HILOS-1 )
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS) +1;
    }
    else
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS);
    }

    int sum=0;
    printf("Hilo %ld, LIM inf %ld LIM sup %ld\n", t, lim_inf, lim_sup);
    for (i = lim_inf; i < lim_sup; i++) {
        for (j = 0; j < columnas2; j++) {
            //r = matriz1[i][k];
            for (z = 0; z < columnas1; z++) {
                //matriz3[i][j] += r*matriz2[k][j];

                sum += matriz1[i][z]*matriz2[z][j];
            }
            matriz3[i][j]=sum;
            sum=0;
        }
    }

    pthread_exit(NULL);
}



template<typename T1>
Matriz<T1> Matriz<T1>::operator * (Matriz<T1> m)
{

    int i,j,z;
    if(columnas == m.filas )
    {
        Matriz<int> R =Matriz<int>(filas,m.columnas);
        for(int i=0;i<filas;i++)
        {
            vector<T1> a;
            for(int j=0;j<m.columnas;j++){
                a.push_back(0);
            }
            matriz3.push_back(a);
        }
        //R.matriz=matriz3;
        matriz1=matriz;
        matriz2=m.matriz;

        int m1,n1,m2,n2,rc;
        long t;
        void* status;

        struct timeval start;
        struct timeval finish;
        long compiletime;
        double Time;
        pthread_t hilos[NUM_HILOS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        gettimeofday(&start, 0);
        for (t = 0;t < NUM_HILOS; t++) {
            datos_pasar[t].thread_id=t;
            datos_pasar[t].num_filas1=filas;
            datos_pasar[t].num_columnas1=columnas;
            datos_pasar[t].num_filas2=m.filas;
            datos_pasar[t].num_columnas2=m.columnas;
            printf("Creando el hilo %ld \n",t);
            rc = pthread_create(&hilos[t],&attr,multiplicar_paralelo,(void*)&datos_pasar[t]);
            if (rc) {
                printf("ERROR codigo %d \n",rc);
                exit(-1);
            }
        }

        pthread_attr_destroy(&attr);

        for(t=0;t<NUM_HILOS;t++) {
            rc = pthread_join(hilos[t],&status);
            if (rc) {
                printf("ERROR,codigo %d \n",rc);
                exit(-1);
            }
            printf("En la funcion main, ya acabo el hilo %ld con status %ld \n",t,(long)status);
        }
        gettimeofday(&finish, 0);
        compiletime = (finish.tv_sec - start.tv_sec)*1000000;
        compiletime = compiletime+(finish.tv_usec-start.tv_usec);
        Time = (double)compiletime;
        cout<<endl;
        printf("Despues de multiplicar con hilos:\n");
        printf("El programa se demoro: %lf segundos.\n", (double)Time/1000000.0);
        //imprimir_matrix(m1,n1,m2,n2);
        R.matriz=matriz3;
        printf("Fin del programa \n");
       // cout<<12;
//        for (int a=0;a<filas;a++) {
//            for (int b=0;b<m.columnas;b++) {
//                printf("%lf \t",matriz3[a][b]);
//            }
//            printf("\n");
//        }
        //return R;
        R.imprimirMatriz();
        pthread_exit(NULL);




    }
    else
        throw runtime_error("No se puede hacer la multiplicación");



}





#endif //PC3_CONCURRENTE_H
